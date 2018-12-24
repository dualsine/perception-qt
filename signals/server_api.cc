#include "server_api.h"
#include "server.h"

#include <iostream>
using namespace std;
#include <string>

namespace Perception {
  namespace Signals {
    namespace {
      Server* server_instance_;
    }

    ServerApi::ServerApi() {
      assert(!server_instance_);
      server_instance_ = new Server();
    }

    void ServerApi::tick() {
      server_instance_->tick();
    }

    void ServerApi::close() {
      server_instance_->close();
    }

  } // namespace Signals
} // namespace Perception
