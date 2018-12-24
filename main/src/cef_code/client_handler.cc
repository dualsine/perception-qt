#include "src/cef_code/client_handler.h"
#include "cef/include/wrapper/cef_helpers.h"

#include <X11/Xatom.h>
#include <X11/Xlib.h>

#include "src/qt_code/elements.h"
#include "src/global_actions.h"

#include <iostream>
using namespace std;

CefClientHandler::CefClientHandler(QPointer<MainWindow> main_window, QPointer<QWidget> browser_widget) {
  Qt::Elements::main_window = main_window;
}

void CefClientHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                               const CefString &title) {
  Qt::Elements::main_window->setWindowTitle(QString::fromStdString(title.ToString()));
}

void CefClientHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 const CefString &url) {
  GlobalActions::addressChanged(browser, frame, url);
}

void CefClientHandler::OnGotFocus(CefRefPtr<CefBrowser> browser) {
  if (Qt::Elements::url_bar)
    Qt::Elements::url_bar->clearFocus();
}

bool CefClientHandler::OnSetFocus(CefRefPtr<CefBrowser> browser, CefFocusHandler::FocusSource source) {
  return false;
}

void CefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CefCore::Instance()->browser = browser;
}

bool CefClientHandler::DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  return false;
}

void CefClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  CefQuitMessageLoop();
}

void CefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                ErrorCode errorCode,
                                const CefString& errorText,
                                const CefString& failedUrl) {
  CEF_REQUIRE_UI_THREAD();

  // Don't display an error for downloaded files.
  if (errorCode == ERR_ABORTED)
    return;

  // Display a load error message.
  std::stringstream ss;
  ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
     << std::string(failedUrl) << " with error " << std::string(errorText)
     << " (" << errorCode << ").</h2></body></html>";
  frame->LoadString(ss.str(), failedUrl);
}


namespace {
bool run_shortcuts(const CefKeyEvent& event, CefEventHandle os_event) {
  if (os_event && os_event->type == KeyPress && os_event->xkey.keycode == 0x09) {
    if (event.focus_on_editable_field == false) {
      GlobalActions::closeApp(); // ESC - exit app
      return true;
    }
  }
  if (os_event && os_event->type == KeyPress && os_event->xkey.keycode == 0x28 && os_event->xkey.state & ShiftMask) {
    if (event.focus_on_editable_field == false) {
      GlobalActions::openDevTools(); // SHIFT+d - open devtools
      return true;
    }
  }
  if (os_event && os_event->type == KeyPress && os_event->xkey.keycode == 0x2e && os_event->xkey.state & ControlMask) {
    GlobalActions::focusUrlBar(); // CTRL+l - focus urlBar
    return true;
  }
  return false;
}
} // namespace

bool CefClientHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event, bool* is_keyboard_shortcut) {
  run_shortcuts(event, os_event);

  return false;
}

// this event starts after all javascript on page has chance to do something with keys
bool CefClientHandler::OnKeyEvent( CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event ) {
  // nothing used this event keys, so send them to qt
  if (os_event && os_event->type == KeyPress && event.focus_on_editable_field == false) {
    GlobalActions::cefSendUnusedKeysBack(event, os_event);
  }
  return false;
}
