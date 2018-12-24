#include "internal_scheme.h"
#include "src/cef_code/core.h"
#include <vector>
#include <boost/algorithm/string/predicate.hpp>

using std::vector;
using std::string;

namespace scheme {
namespace {

string getFilePath(vector<string> splitted_url) {
  string file_path = "";
  for(int i=1;
      i < static_cast<int>(splitted_url.size());
      i++){
    if (file_path != "") file_path += "/";
    file_path += splitted_url[(size_t)i];
  }

  if (splitted_url.size() == 2) file_path += "/index.html";

  return file_path;
}

string loadResourceFile(string file_path) {
  string res;
  string path = ":/internal_scheme_frontend/dist/"+file_path;
  QString fileName(path.c_str());
  QFile file(fileName);
  if(!file.open(QIODevice::ReadOnly))
    throw "filenot opened:"+file_path;
  else res = file.readAll().toStdString();
  file.close();
  return res;
}

vector<string> splitUrl(string url) {
  vector<string> res;
  size_t pos = 0;
  string delimiter = "/";
  while ((pos = url.find(delimiter)) != string::npos) {
      string chunk =  url.substr(0, pos);
      if (chunk != "") res.push_back(chunk);
      url.erase(0, pos + delimiter.length());
  }
  if (url != "") res.push_back(url);
  return res;
}

bool InternalScheme::ProcessRequest(CefRefPtr<CefRequest> request,
                    CefRefPtr<CefCallback> callback) {
  CEF_REQUIRE_IO_THREAD();

  bool handled = false;

  string url = request->GetURL();
  vector<string> splitted_url = splitUrl(url);

  string file_path = getFilePath(splitted_url);

  string file = loadResourceFile(file_path);
  if (file.empty()) throw "no such file:" + url;
  else {
    if (boost::algorithm::ends_with(file_path, ".html")) mime_type_ = "text/html";
    if (boost::algorithm::ends_with(file_path, ".png")) mime_type_ = "image/png";
    if (boost::algorithm::ends_with(file_path, ".jpg")) mime_type_ = "image/jpeg";
    if (boost::algorithm::ends_with(file_path, ".jpeg")) mime_type_ = "image/jpeg";
    if (boost::algorithm::ends_with(file_path, ".svg")) mime_type_ = "image/svg+xml";
    if (boost::algorithm::ends_with(file_path, ".js")) mime_type_ = "application/javascript";
    if (boost::algorithm::ends_with(file_path, ".css")) mime_type_ = "text/css";
    data_ = file;
    handled = true;
  }

  if (handled) {
    // Indicate the headers are available.
    callback->Continue();
    return true;
  }

  return false;
}

void InternalScheme::GetResponseHeaders(CefRefPtr<CefResponse> response,
                        int64& response_length,
                        CefString& redirectUrl) {
  CEF_REQUIRE_IO_THREAD();

  DCHECK(!data_.empty());

  response->SetMimeType(mime_type_);
  response->SetStatus(200);

  // Set the resulting response length.
  response_length = data_.length();
}

bool InternalScheme::ReadResponse(void* data_out,
                  int bytes_to_read,
                  int& bytes_read,
                  CefRefPtr<CefCallback> callback) {
  CEF_REQUIRE_IO_THREAD();

  bool has_data = false;
  bytes_read = 0;

  if (offset_ < data_.length()) {
    // Copy the next block of data into the buffer.
    int transfer_size =
        std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
    memcpy(data_out, data_.c_str() + offset_, static_cast<size_t>(transfer_size));
    offset_ += static_cast<uint>(transfer_size);

    bytes_read = transfer_size;
    has_data = true;
  }

  return has_data;
}

} // namespace

void RegisterInternalSchemeFactory() {
  CefRegisterSchemeHandlerFactory("internal", "", new InternalSchemeFactory()); // 2 argument is "" for every domain
}

} // namespace scheme
