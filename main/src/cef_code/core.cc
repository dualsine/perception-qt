#include "core.h"
#include "cef/include/cef_app.h"
#include "dev_tools_handler.h"
#include "internal_scheme.h"
#include "blink_signals.h"
#include "app_class/app_browser.h"
#include "app_class/app_other.h"
#include "app_class/app_renderer.h"

#include <iostream>
using namespace std;

CefRefPtr<CefBrowser> CefCore::browser;
QPointer<CefWidget> CefCore::cef_widget;
bool CefCore::internal_pages_active = false;
std::string CefCore::last_url = "about:blank";

namespace {
  CefCore* instance_ = nullptr;
}

// retrieve args on linux platform
cef_main_args_t CefCore::MainArgs(int argc, char *argv[]) {
  return cef_main_args_t { argc, argv };
}

CefCore::CefCore(int argc, char *argv[]) {
  DCHECK(!instance_);
  instance_ = this;

  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromArgv(argc, argv);

  CefEnableHighDPISupport();

  CefRefPtr<CefApp> cefapp;
  Perception::Cef::ProcessType process_type = Perception::Cef::GetProcessType(command_line);
  if (process_type == Perception::Cef::ProcessType::BrowserProcess) {
    cout << "initialize browser process with thread_id:" << std::this_thread::get_id() << endl;
    cefapp = new Perception::Cef::AppBrowser();
  } else if (process_type == Perception::Cef::ProcessType::RendererProcess ||
             process_type == Perception::Cef::ProcessType::ZygoteProcess) {
    // On Linux the zygote process is used to spawn other process types. Since
    // we don't know what type of process it will be give it the renderer
    // client.
    cout << "initialize renderer process with thread_id:" << std::this_thread::get_id() << endl;
    cefapp = new Perception::Cef::AppRenderer();
  } else if (process_type == Perception::Cef::ProcessType::OtherProcess) {
    cout << "initialize other process with thread_id:" << std::this_thread::get_id() << endl;
    cefapp = new Perception::Cef::AppOther();
  }

  CefMainArgs main_args(this->MainArgs(argc, argv));

  int exit_code = CefExecuteProcess(main_args, cefapp, nullptr);
  if (exit_code < 0) { // `exit_code >= 0` - child process
    CefSettings settings;
    settings.no_sandbox = true;
    if (!CefInitialize(main_args, settings, cefapp, nullptr)) {
      throw std::runtime_error("Unable to initialize CEF");
    }

    scheme::RegisterInternalSchemeFactory();
  }
}

CefCore::~CefCore() {
  instance_ = nullptr;
}

void CefCore::tick() {
  CefDoMessageLoopWork();
}

void CefCore::openDevTools() {
  CefWindowInfo wi;
  CefBrowserSettings s;
  CefPoint p;
  CefDevToolsHandler *dev = new CefDevToolsHandler();
  CefCore::browser->GetHost()->ShowDevTools(wi, dev, s, p);
}

CefCore* CefCore::Instance() {
  return instance_;
}
