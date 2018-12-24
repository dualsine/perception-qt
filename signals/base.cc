#include "base.h"

namespace Perception {
  namespace Signals {
    
    void* Base::context_;
    void* Base::socket_;
    const std::string Base::port_ = "1774";
    bool Base::loop_active_ = true; // server and client are in other processes - so change this on one side dont't affects other

  } // namespace Signals
} // namespace Perception