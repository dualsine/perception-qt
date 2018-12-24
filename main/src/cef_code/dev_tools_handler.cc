#include "dev_tools_handler.h"

namespace {

  CefDevToolsHandler* _instance = NULL;

}  // namespace

CefDevToolsHandler::CefDevToolsHandler() {
  DCHECK(!_instance);
  _instance = this;
}

CefDevToolsHandler::~CefDevToolsHandler() {
  _instance = NULL;
}

CefDevToolsHandler* CefDevToolsHandler::GetInstance() {
  return _instance;
}
