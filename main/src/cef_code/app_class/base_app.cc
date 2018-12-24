#include "src/cef_code/app_class/base_app.h"

namespace Perception {
  namespace Cef {

    ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line) {
      if (!command_line->HasSwitch(kProcessType))
        return BrowserProcess;

      const std::string& process_type = command_line->GetSwitchValue(kProcessType);
      if (process_type == kRendererProcess)
        return RendererProcess;
      #if defined(OS_LINUX)
      else if (process_type == kZygoteProcess)
        return ZygoteProcess;
      #endif
      return OtherProcess;
    }

    BaseApp::BaseApp() {}

  } // namespace Cef
} // namespace Perception
