#pragma once
#ifndef PERCEPTION_SIGNALS_CLIENT_H_
#define PERCEPTION_SIGNALS_CLIENT_H_

#include "../base.h"
#include <vector>

namespace Perception {
  namespace Signals{

    class Client : public Base {
    public:
      Client();
      static void createInstance();
      static void sendMessage(const std::string msg);
    private:
      static void* client_loop_(void*);
      static std::vector<char*> msg_queue_;
      pthread_t thread_;
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_CLIENT_H_