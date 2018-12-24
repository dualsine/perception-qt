#pragma once
#ifndef PERCEPTION_SIGNALS_DESERIALIZATOR_H_
#define PERCEPTION_SIGNALS_DESERIALIZATOR_H_

#include "utils.h"

namespace Perception {
  namespace Signals {

    class Deserializator {
    public:
      inline Deserializator(std::string input) {
        input_ = input;
        oryginal_string_ = input;
        event_id_ = std::stoi(deserializeField());
      }

      inline int eventId() {
        return event_id_;
      }

      inline std::string next() {
        return deserializeField();
      }

      inline std::string deserializeField(bool remove = true) {
        int max_pos, newline_pos;
        newline_pos = input_.find("\n");
        if (newline_pos < 0) max_pos = input_.length();
        else max_pos = newline_pos + 1;

        std::string field = input_.substr(0, max_pos-1).c_str();
        if (remove) input_.erase(0, max_pos);
        return base64_decode(field);
      }
    private:
      int event_id_;
      std::string input_;
      std::string oryginal_string_;
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_DESERIALIZATOR_H_