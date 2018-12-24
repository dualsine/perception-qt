#include "src/cef_code/app_class/app_renderer.h"

namespace Perception {
  namespace Cef {
    void AppRenderer::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
      Q_UNUSED(browser)
      CEF_REQUIRE_RENDERER_THREAD();
    }

    void AppRenderer::OnContextCreated(CefRefPtr<CefBrowser> browser,
              CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
      Q_UNUSED(browser)
      CEF_REQUIRE_RENDERER_THREAD();

      CefRefPtr<CefInspector> inspector = CreateInspector(frame, context);
      inspector->TestRun();
    }
  } // namespace Cef
} // namespace Perception
