#include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
    const int id = str[0]-'0';
    const bool value = str[2]-'0';
    std::cout << instance()->activeSensorsNum << "\n";
    if(bool(id>= 0) && bool(id<SENSOR_COUNT)){
	instance_->sensorMutex.lock();
        if(instance_->enabledSensors[id]){
            std::cout<<"Le capteur #"<<id<<" est passé à l'état "<<value<<'\n';
            instance_->sensorValues[id]=value;
            if(value){
	        std::cout << "pause\n";
                Utils::AsservUtil::instance()->pause();
                instance_->activeSensorsNum++;
            }else{
                instance_->activeSensorsNum--;
                if (!(instance_->activeSensorsNum>1)) Utils::AsservUtil::instance()->resume();
            }
        }
        instance_->sensorMutex.unlock();
    }
    #ifdef DEBUG
    std::cout<<"DEBUG SENSORS: "+str+"\n";
    #endif
}

void Utils::SensorUtil::enableSensor(int id){
    instance()->sensorMutex.lock();
    instance_->enabledSensors[id]=true;
    if(instance_->sensorValues[id]) instance_->activeSensorsNum++;
    if(instance_->activeSensorsNum>1) Utils::AsservUtil::instance()->pause();
    instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::reset() {
    instance()->sensorMutex.lock();
    for(int i=0; i<SENSOR_COUNT; i++) {
	instance_->enabledSensors[i] = false;
    instance_->sensorValues[i] = false;
    }
    instance_->activeSensorsNum = 0;
    instance_->module_->sendCommand("dsensors;");
    instance_->sensorMutex.unlock();
}

Utils::SensorUtil *Utils::SensorUtil::instance(){
    if(!instance()){
        instance_ = new SensorUtil;
        #ifdef DEBUG
        std::cout << "Instance de SensorUtil créée\n";
        #endif
    }
    return instance_;
}
