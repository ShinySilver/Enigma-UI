#include "testProtocol.hpp"
#include "../Protocols/robot.h"
#include "../IA/ia.hpp"

void TestProtocol::update(){ //execute the next action of this protocol
  switch(state){
    case 0:
    //ia->mb->translate(500);
    break;
    case 1:
    //ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 2:
    //ia->mb->translate(500);
    break;
    case 3:
    //ia->mb->rotate(PI*(ia->getFlag("side")?1:-1));
    break;
    case 4:
    //ia->mb->translate(500);
    break;
    case 5:
    //ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 6:
    //ia->mb->translate(500);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

bool TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>7;
}

unsigned short int TestProtocol::getPriority(){
  return priority;
}
