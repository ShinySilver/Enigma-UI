#include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
    if((int)str[0]>= 0 && (int)str[0]<SENSOR_COUNT){
        instance()->sensorMutex.lock();
        if(instance_->enabledSensors[(int)str[0]]){
            std::cout<<"Le capteur #"<<str[0]<<" est passé à l'état "<<str[2]<<'\n';
            instance_->sensorValues[(int)str[0]]=(bool)str[2];
            if((int)str[2]==1){
                Utils::AsservUtil::instance()->pause();
                instance_->activeSensorsNum++;
            }else{
                instance_->activeSensorsNum--;
                if (!instance_->activeSensorsNum) Utils::AsservUtil::instance()->resume();
            }
        }
        instance_->sensorMutex.unlock();
    }
    #ifdef DEBUG
    std::cout<<"DEBUG SENSORS: "+str+"\n";
    #endif
}

void Utils::SensorUtil::enableSensor(int id){
    enabledSensors[id]=true;
    if(sensorValues[id]) activeSensorsNum++;
    if (activeSensorsNum) Utils::AsservUtil::instance()->pause();
}

Utils::SensorUtil *Utils::SensorUtil::instance(){
    if(!instance_){
        instance_ = new SensorUtil;
        #ifdef DEBUG
        std::cout << "Instance de SensorUtil créée\n";
        #endif
    }
    return instance_;
}
