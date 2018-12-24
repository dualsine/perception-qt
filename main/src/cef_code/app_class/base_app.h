#pragma once
#ifndef PERCEPTION_CEF_BASE_APP_H_
#define PERCEPTION_CEF_BASE_APP_H_

#include <QtGlobal>
#include "cef/include/wrapper/cef_helpers.h"
#include "cef/include/cef_app.h"

namespace Perception {
  namespace Cef {

    const char kProcessType[] = "type";
    const char kRendererProcess[] = "renderer";
    #if defined(OS_LINUX)
    const char kZygoteProcess[] = "zygote";
    #endif
    enum ProcessType {
      BrowserProcess,
      RendererProcess,
      ZygoteProcess,
      OtherProcess,
    };

    ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line);

    class BaseApp : public CefApp {
    public:
      BaseApp();

    private:
      IMPLEMENT_REFCOUNTING(BaseApp)
    };
  } // namespace Cef
} // namespace Perception

#endif
