#ifndef INTERNAL_SCHEME_H
#define INTERNAL_SCHEME_H

#include "cef/include/cef_browser.h"
#include "cef/include/cef_callback.h"
#include "cef/include/cef_frame.h"
#include "cef/include/cef_request.h"
#include "cef/include/cef_resource_handler.h"
#include "cef/include/cef_response.h"
#include "cef/include/cef_scheme.h"
#include "cef/include/wrapper/cef_helpers.h"

namespace scheme {

namespace {

class InternalScheme : public CefResourceHandler {
 public:
  InternalScheme() : offset_(0) {}

  bool ProcessRequest(CefRefPtr<CefRequest> request,
                      CefRefPtr<CefCallback> callback) override;

  void GetResponseHeaders(CefRefPtr<CefResponse> response,
                          int64& response_length,
                          CefString& redirectUrl) override;

  void Cancel() override { CEF_REQUIRE_IO_THREAD(); }

  bool ReadResponse(void* data_out,
                    int bytes_to_read,
                    int& bytes_read,
                    CefRefPtr<CefCallback> callback) override;

 private:
  std::string data_;
  std::string mime_type_;
  size_t offset_;

  IMPLEMENT_REFCOUNTING(InternalScheme)
  DISALLOW_COPY_AND_ASSIGN(InternalScheme);
};

// Implementation of the factory for creating scheme handlers.
class InternalSchemeFactory : public CefSchemeHandlerFactory {
public:
  InternalSchemeFactory() {}

  // Return a new scheme handler instance to handle the request.
  CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefFrame> frame,
                                       const CefString& scheme_name,
                                       CefRefPtr<CefRequest> request) override {
    CEF_REQUIRE_IO_THREAD();
    return new InternalScheme();
  }

private:
  IMPLEMENT_REFCOUNTING(InternalSchemeFactory)
  DISALLOW_COPY_AND_ASSIGN(InternalSchemeFactory);
};

} // namespace

void RegisterInternalSchemeFactory();

} // namespace scheme

#endif // INTERNAL_SCHEME_H
