#pragma once
#ifndef PERCEPTION_SIGNALS_SERVER_H
#define PERCEPTION_SIGNALS_SERVER_H

#include "../signals/server_api.h"

namespace Perception {

class SignalsServer : public Perception::Signals::ServerApi {
public:
  SignalsServer();
};

} // namespace SignalsServer

#endif // PERCEPTION_SIGNALS_SERVER_H
