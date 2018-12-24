#pragma once
#ifndef PERCEPTION_CEF_CEF_APP_OTHER_H_
#define PERCEPTION_CEF_CEF_APP_OTHER_H_

#include "src/cef_code/app_class/base_app.h"

namespace Perception {
  namespace Cef {

    class AppOther : public BaseApp {
    public:
      AppOther();
    private:
      IMPLEMENT_REFCOUNTING(AppOther)
      DISALLOW_COPY_AND_ASSIGN(AppOther);
    };

  } // namespace Cef
} // namespace Perception

#endif
