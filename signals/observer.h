#pragma once
#ifndef PERCEPTION_SIGNALS_OBSERVER_H_
#define PERCEPTION_SIGNALS_OBSERVER_H_

#include <vector>

#include <iostream>
using namespace std;

namespace Perception {
  namespace Signals {

    class Observer {
    public:
      Observer();

      static std::vector<Observer*> getObservers();
      
      virtual void OnMouseClick(float x, float y) = 0;

    private:
      static std::vector<Observer*> observers;
    };

  } // namespace Signals
} // namespace Perception

#endif // PERCEPTION_SIGNALS_OBSERVER_H_
