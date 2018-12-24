#pragma once
#ifndef PERCEPTION_SIGNALS_SERIALIZATOR_H_
#define PERCEPTION_SIGNALS_SERIALIZATOR_H_

#include "utils.h"

#include <sstream>

namespace Perception {
  namespace Signals{

    class Serializator {
    public:
      inline Serializator(int event_type) {
        serialized_ << base64_encode(std::to_string(event_type)) << std::endl;
      };
      
      inline void serializeField(std::string value) {
        serialized_  << base64_encode(value) << std::endl;
      }

      inline std::string out() {
        return serialized_.str();
      }

    private:
      std::ostringstream serialized_;
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_SERIALIZATOR_H_