#include "observer.h"

namespace Perception {
  namespace Signals {
      
    std::vector<Observer*> Observer::observers;

    Observer::Observer() {
      Observer::observers.push_back(this);
    }

    std::vector<Observer*> Observer::getObservers() {
      return observers;
    }
    
  } // namespace Signals
} // namespace Perception
