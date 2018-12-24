#ifndef GLOBALACTIONS_H
#define GLOBALACTIONS_H

#include "cef/include/cef_app.h"

class GlobalActions
{
public:
  static void closeApp();
  static void openDevTools();
  static void openUrl(std::string url);
  static void addressChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                            const CefString &url);
  static void switchOptionsPage();
  static void loadInternalPage(std::string domain);
  static void cefSendUnusedKeysBack(const CefKeyEvent& event, CefEventHandle os_event);
  static void focusUrlBar();
  static void unfocusUrlBar();
};

#endif // GLOBALACTIONS_H
