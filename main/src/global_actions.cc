#include "src/global_actions.h"
#include <unistd.h>
#include <QApplication>
#include "src/qt_code/elements.h"
#include "src/cef_code/core.h"
#include "src/keys_enum.h"

void GlobalActions::closeApp() {
  CefShutdown();
  QApplication::quit();
}

void GlobalActions::openDevTools() {
  CefCore::Instance()->openDevTools();
}

void GlobalActions::openUrl(std::string url) {
  if (url.find("internal://") == 0) {
    // don't allow user load internal pages
  } else {
    CefCore::browser->GetMainFrame()->LoadURL(CefString(url));
  }
}

void GlobalActions::addressChanged(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  const CefString &url) {
  std::string surl = url.ToString();
  if (frame->IsMain() && Qt::Elements::url_bar) {
    if (surl.rfind("internal://",0) == 0) {
      Qt::Elements::url_bar->setDisabled(true);
    } else {
      CefCore::last_url = url;
      Qt::Elements::url_bar->setDisabled(false);
      Qt::Elements::url_bar->setText(QString::fromStdString(surl));
    }
  }
}

void GlobalActions::switchOptionsPage() {
  if (CefCore::internal_pages_active)
    GlobalActions::openUrl( CefCore::last_url );
  else GlobalActions::loadInternalPage("options");

  CefCore::internal_pages_active = !CefCore::internal_pages_active;
}

void GlobalActions::loadInternalPage(std::string domain) {
  CefCore::browser->GetMainFrame()->LoadURL(CefString("internal://"+domain));
}

void GlobalActions::cefSendUnusedKeysBack(const CefKeyEvent& event, CefEventHandle os_event) {
  QWidget *focused_widget = qApp->focusWidget();
  if (dynamic_cast<QLineEdit*>(focused_widget) != nullptr) {
    Qt::Key qt_key_type = KeysEnum::getQtKeyCodeFromGtk(os_event);

    Qt::KeyboardModifier mod = KeysEnum::getModifier(os_event);
    if (mod == Qt::ControlModifier && qt_key_type == Qt::Key_A) {
      QTimer::singleShot(0, focused_widget, SLOT(selectAll()));
    }

    QKeyEvent *key_evt = new QKeyEvent(QKeyEvent::KeyPress, qt_key_type, mod, QString(event.character));
    QApplication::sendEvent(focused_widget, key_evt);
  }
}

void GlobalActions::focusUrlBar() {
  Qt::Elements::url_bar->setFocus();
  QTimer::singleShot(0, Qt::Elements::url_bar, SLOT(selectAll()));
}

void GlobalActions::unfocusUrlBar() {
  Qt::Elements::url_bar->clearFocus();
}
