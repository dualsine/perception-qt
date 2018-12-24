#pragma once
#ifndef PERCEPTION_SIGNALS_SERVER_API_H_
#define PERCEPTION_SIGNALS_SERVER_API_H_

namespace Perception {
  namespace Signals {
    
    class ServerApi {
    public:
      ServerApi();

      static void tick();

      void close();
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_SERVER_API_H_
