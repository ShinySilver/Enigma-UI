#include <thread>
#include <iostream>

#include "Settings.hpp"

namespace Utils{
  void starter(int pin) {
    #ifdef PI
    double tmp = 0;
    bool hasStarterBeenInserted = false;
    while (true) {
      tmp = (double)(tmp * 95.0 + digitalRead(pin)) / 100.0;
      if (!hasStarterBeenInserted && tmp >= 0.90) {
        Utils::Settings::setFlag("isStarterReady",1);
      }
      if(hasStarterBeenInserted && tmp <= 0.10){
        return;
      }
      delay(1);
    }
    #else
    (void)pin;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Utils::Settings::setFlag("isStarterReady",1);
    std::cout<<"Starter inserted!\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    Utils::Settings::setFlag("isStarted",1);
    std::cout<<"Starter removed. Robot launched!\n";
    #endif
  }
}
