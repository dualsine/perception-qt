#pragma once
#ifndef PERCEPTION_CEF_APP_BROWSER_H_
#define PERCEPTION_CEF_APP_BROWSER_H_

#include "src/cef_code/app_class/base_app.h"

namespace Perception {
  namespace Cef {

    class AppBrowser : public BaseApp, public CefBrowserProcessHandler {
    public:
      AppBrowser() {}

      virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

      // CefApp methods
      virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;
      // CefBrowserProcessHandler methods
      virtual void OnContextInitialized() override;

    private:
      IMPLEMENT_REFCOUNTING(AppBrowser)
      DISALLOW_COPY_AND_ASSIGN(AppBrowser);
    };

  } // namespace Cef
} // namespace Perception

#endif
