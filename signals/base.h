#pragma once
#ifndef PERCEPTION_SIGNALS_BASE_H_
#define PERCEPTION_SIGNALS_BASE_H_

#include "utils.h"

#include "zmq.h"
#include "zhelpers.h"

namespace Perception {
  namespace Signals {

    class Base {
    protected:
      static const std::string port_;
      static void* context_;
      static void* socket_;
      static bool loop_active_;
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_BASE_H_
