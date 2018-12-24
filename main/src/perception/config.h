#pragma once
#ifndef PERCEPTION_CONFIG_H_
#define PERCEPTION_CONFIG_H_

#include "src/cef_code/blink_signals.h"
#include "src/perception/signals_server.h"

namespace Perception {

  class Config {
  public:
    static BlinkSignals* bs;
    static SignalsServer* ss;
  };

} // namespace Perception

#endif
