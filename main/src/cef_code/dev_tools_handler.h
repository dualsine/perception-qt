#ifndef CEF_DEV_TOOLS_HANDLER_H
#define CEF_DEV_TOOLS_HANDLER_H

#include "cef/include/cef_client.h"

class CefDevToolsHandler : public CefClient {
public:
  explicit CefDevToolsHandler();
  ~CefDevToolsHandler() override;

  // Provide access to the single global instance of this object.
  static CefDevToolsHandler* GetInstance();

private:
  CefRefPtr<CefBrowser> browser_;

  IMPLEMENT_REFCOUNTING(CefDevToolsHandler)
};


#endif // CEF_DEV_TOOLS_HANDLER_H
