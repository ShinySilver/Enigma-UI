#include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
    if((int)str[0]>= 0 && (int)str[0]<SENSOR_COUNT
            && instance()->enabledSensors[(int)str[0]]==true){
        std::cout<<"Le capteur #"<<str[0]<<" est passé à l'état "<<str[2]<<'\n';
        if((int)str[2]==1){
            Utils::AsservUtil::instance()->pause();
        }else{
            Utils::AsservUtil::instance()->resume();
        }
    }
    #ifdef DEBUG
    std::cout<<"DEBUG SENSORS: "+str+"\n";
    #endif
}
