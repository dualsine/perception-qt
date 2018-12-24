#include "src/cef_code/bindings_qt/widget.h"
#include <X11/Xlib.h>
#include "cef/include/cef_client.h"
#include "src/cef_code/client_handler.h"
#include "src/qt_code/main_window.h"
#include "src/qt_code/elements.h"

QPointer<QWidget> CefWidget::embedBrowser(MainWindow *main_window) {
  CefWindowInfo win_info;
  window = new CefEmbedWindow(this);
  win_info.SetAsChild(static_cast<CefWindowHandle>(window->winId()),
                      CefRect(0, 0, width(), height()));
  CefBrowserSettings settings;
  CefRefPtr<CefClientHandler> handler(new CefClientHandler(main_window, this));
  browser_ = CefBrowserHost::CreateBrowserSync(win_info,
                                               handler,
                                               CefString("about:blank"),
                                               settings,
                                               nullptr);
  embedded_widget = QWidget::createWindowContainer(window, main_window);
  return embedded_widget;
}

void CefWidget::updateSize() {
  if (browser_) {
    auto browser_host = browser_->GetHost();
    auto browser_win = browser_host->GetWindowHandle();
    auto xdisplay = cef_get_xdisplay();
    XWindowChanges changes = {};
    changes.x = 0;
    changes.y = 0;
    changes.width = width();
    changes.height = height();
    XConfigureWindow(xdisplay,
                     browser_win,
                     CWX | CWY | CWHeight | CWWidth,
                     &changes);
    browser_host->NotifyMoveOrResizeStarted();
  }
}
