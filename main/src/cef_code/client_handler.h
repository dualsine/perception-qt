#ifndef CEF_CLIENT_HANDLER_H_
#define CEF_CLIENT_HANDLER_H_

#include <QtWidgets>
#include "cef/include/cef_client.h"
#include "src/cef_code/core.h"
#include "src/qt_code/main_window.h"

class CefClientHandler :
    public CefClient,
    public CefDisplayHandler,
    public CefFocusHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefKeyboardHandler {
public:
  explicit CefClientHandler(QPointer<MainWindow> main_window,
                      QPointer<QWidget> browser_widget);

  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  virtual CefRefPtr<CefFocusHandler> GetFocusHandler() override { return this; }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override { return this; }

  // CefDisplayHandler methods
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
  virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                               const CefString& url) override;
  // CefFocusHandler methods
  virtual void OnGotFocus(CefRefPtr<CefBrowser> browser) override;
  virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser, CefFocusHandler::FocusSource source);
  // CefLifeSpanHandler methods
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
  // CefLoadHandler methods:
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) override;
  // CefKeyboardHandler methods:
  virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event,
                             bool* is_keyboard_shortcut) override;
  virtual bool OnKeyEvent( CefRefPtr< CefBrowser > browser, const CefKeyEvent& event, CefEventHandle os_event ) override;

private:
  IMPLEMENT_REFCOUNTING(CefClientHandler)
};

#endif // QT_CEF_POC_HANDLER_H_
