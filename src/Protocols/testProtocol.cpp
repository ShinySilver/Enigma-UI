#include "testProtocol.hpp"
#include "../Protocols/robot.h"
#include "../IA/ia.hpp"

#include "../Utils/asservUtil.hpp"
#include "../Utils/sensorUtil.hpp"

void TestProtocol::update(){ //execute the next action of this protocol
  switch(state_){
    case 0:
    std::cout<<text_;
    break;
    case 1:
    if(!translation_) break;
    Utils::SensorUtil::instance()->reset();
    Utils::SensorUtil::instance()->enableSensor(FRONT_LEFT_SENSOR);
    Utils::SensorUtil::instance()->enableSensor(FRONT_RIGHT_SENSOR);
    Utils::AsservUtil::instance()->forward(-200);
    while(Utils::AsservUtil::instance()->isBusy()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    break;
    case 2:
    Utils::AsservUtil::instance()->forward(400);
    while(Utils::AsservUtil::instance()->isBusy()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    break;
    case 3:
    Utils::AsservUtil::instance()->forward(translation_);
    while(Utils::AsservUtil::instance()->isBusy()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    break;
    case 4:
    Utils::AsservUtil::instance()->rotate(-PI/2);
    while(Utils::AsservUtil::instance()->isBusy()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    break;
    case 5:
    Utils::AsservUtil::instance()->forward(translation_);
    while(Utils::AsservUtil::instance()->isBusy()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    break;
    default:
    // Anomaly
    break;
  }
  state_++;
}

bool TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state_>2||(translation_==0&&state_>1);
}

unsigned short int TestProtocol::getPriority(){
  return priority_;
}
