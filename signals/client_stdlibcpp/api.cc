#include "api.h"
#include "client.h"
#include "../serializator.h"
#include "../events.h"

namespace Perception {
  namespace Signals{

    void Api::createClient() {
      Client::createInstance();
    }

    void Api::sendMouseClick(float x, float y) {
      Serializator mouse_click(Events::MouseClick);
      mouse_click.serializeField(ftos(x));
      mouse_click.serializeField(ftos(y));
      Client::sendMessage(mouse_click.out());
    }

  } // namespace Signals
} // namespace Perception