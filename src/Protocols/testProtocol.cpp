#include "testProtocol.hpp"
#include "../Protocols/robot.h"
#include "../IA/ia.hpp"

#include "../Utils/asservUtil.hpp"

void TestProtocol::update(){ //execute the next action of this protocol
  switch(state_){
    case 0:
    std::cout<<text_;
    break;
    case 1:
    Utils::AsservUtil::instance()->forward(translation_);
    break;
    case 2:
    //ia->mb->translate(500);
    break;
    case 3:
    //ia->mb->rotate(PI*(ia->getFlag("side")?1:-1));
    break;
    default:
    // Anomaly
    break;
  }
  state_++;
}

bool TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state_>3;
}

unsigned short int TestProtocol::getPriority(){
  return priority_;
}
