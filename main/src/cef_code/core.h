#pragma once
#ifndef CEF_CORE_H_
#define CEF_CORE_H_

#include "QApplication"
#include "src/cef_code/dev_tools_handler.h"
#include "src/cef_code/bindings_qt/widget.h"

class CefWidget;

class CefCore {
public:
  static CefRefPtr<CefBrowser> browser;
  static QPointer<CefWidget> cef_widget;
  static bool internal_pages_active;
  static std::string last_url;
  static bool unfocus_active;

  CefCore(int argc, char *argv[]);
  ~CefCore();

  void openDevTools();
  void tick();

  static CefCore* Instance();

private:
  cef_main_args_t MainArgs(int argc, char *argv[]);
};

#endif // QT_CEF_POC_CEF_H_
