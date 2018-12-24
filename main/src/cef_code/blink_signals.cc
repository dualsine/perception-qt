#include "blink_signals.h"
#include "src/qt_code/elements.h"

#include <iostream>
using namespace std;

namespace Perception {

  BlinkSignals::BlinkSignals() : Observer() {}
  BlinkSignals::~BlinkSignals() {}

  void BlinkSignals::OnMouseClick(float x, float y) {
    cout << "in onclick" << endl;
    cout << "x:" << x << " y:" << y << endl;
  }

} // namespace Perception
