#pragma once
#ifndef PERCEPTION_SIGNALS_CLIENT_API_H_
#define PERCEPTION_SIGNALS_CLIENT_API_H_

namespace Perception {
  namespace Signals {
        
    class Api {
    public:
      static void createClient();

      static void sendMouseClick(float x, float y);
    private:
      Api();
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_CLIENT_API_H_