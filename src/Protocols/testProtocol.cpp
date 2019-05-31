#include "testProtocol.hpp"
#include "../Protocols/robot.h"
#include "../IA/ia.hpp"

#include "../Utils/asservUtil.hpp"
#include "../Utils/sensorUtil.hpp"
#include "../Utils/Settings.hpp"

void TestProtocol::update(){ //execute the next action of this protocol
  switch(state_){
    case 0:
    std::cout<<text_;
    break;
    case 1:
    Utils::SensorUtil::instance()->reset();
    Utils::SensorUtil::instance()->enableSensor(FRONT_LEFT_SENSOR);
    Utils::SensorUtil::instance()->enableSensor(FRONT_RIGHT_SENSOR);
    Utils::SensorUtil::instance()->enableSensor(1);
    Utils::SensorUtil::instance()->enableSensor(3);
    Utils::SensorUtil::instance()->enableSensor(8);
    Utils::SensorUtil::instance()->enableSensor(7);
    Utils::AsservUtil::instance()->forward(1000);
    break;
    case 2:
    Utils::AsservUtil::instance()->rotate(Utils::Settings::getFlag("isLeftSide")?PI/2:-PI/2);
    break;
    case 3:
    Utils::AsservUtil::instance()->forward(300);
    break;
    case 4:
    Utils::AsservUtil::instance()->rotate(Utils::Settings::getFlag("isLeftSide")?PI/2:-PI/2);
    break;
    case 5:
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    break;
    case 6:
    if(!translation_) break;
    Utils::AsservUtil::instance()->forward(1000);
    break;
    default:
    // Anomaly
    break;
  }
  state_++;
}

bool TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state_>6;
}

unsigned short int TestProtocol::getPriority(){
  return priority_;
}
