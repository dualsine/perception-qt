#include "src/cef_code/app_class/app_browser.h"
#include "cef/include/wrapper/cef_helpers.h"

namespace Perception {
  namespace Cef {

    void AppBrowser::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
      registrar->AddCustomScheme(CefString("internal"), true, false, false, true, false, false);
    }

    void AppBrowser::OnContextInitialized() {
      CEF_REQUIRE_UI_THREAD();
    }

  } // namespace Cef
} // namespace Perception
