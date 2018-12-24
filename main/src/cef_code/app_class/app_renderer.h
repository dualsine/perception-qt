#pragma once
#ifndef PERCEPTION_CEF_APP_RENDERER_H_
#define PERCEPTION_CEF_APP_RENDERER_H_

#include "src/cef_code/app_class/base_app.h"

namespace Perception {
  namespace Cef {

    class AppRenderer : public BaseApp, public CefRenderProcessHandler {
    public:
      AppRenderer() {}

      virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }

      // CefRenderProcessHandler methods
      virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) override;
      virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefV8Context> context) override;

    private:
      IMPLEMENT_REFCOUNTING(AppRenderer)
      DISALLOW_COPY_AND_ASSIGN(AppRenderer);
    };

  } // namespace Cef
} // namespace Perception

#endif
