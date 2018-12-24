#ifndef BLINK_SIGNALS_H
#define BLINK_SIGNALS_H

#include <QApplication>
#include "../signals/observer.h"

namespace Perception {

  class BlinkSignals : public Signals::Observer {
  public:
    BlinkSignals();
    virtual ~BlinkSignals();
    virtual void OnMouseClick(float x, float y) override;
//    static void* run(void*);
  };

} // namespace Perception

#endif // BLINK_SIGNALS_H
