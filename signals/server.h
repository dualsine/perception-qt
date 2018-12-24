#pragma once
#ifndef PERCEPTION_SIGNALS_SERVER_H_
#define PERCEPTION_SIGNALS_SERVER_H_

#include "base.h"

namespace Perception {
  namespace Signals {

    class Server : public Base {
    public:
      Server();
      void tick();
      void close();
      std::string socketRecvAsync(void* socket);
    private:
      void sendMessage(const std::string msg, std::string remote_identity);
      void getMessage(std::string &message, std::string &identity);
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_SERVER_H_
