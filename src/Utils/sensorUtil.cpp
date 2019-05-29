#include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
<<<<<<< HEAD
    const int id = str[0]-'0';
    const bool value = str[2]-'0';
    std::cout << instance_->activeSensorsNum << "\n";
    if(bool(id>= 0) && bool(id<SENSOR_COUNT)){
	instance()->sensorMutex.lock();
        if(instance_->enabledSensors[id]){
            std::cout<<"Le capteur #"<<id<<" est passé à l'état "<<value<<'\n';
            instance_->sensorValues[id]=value;
            if(value){
	        std::cout << "pause\n";
=======
    std::cout<<"sensor #"<<str[0]-'0'<<" passe à "<<str[2]-'0'<<"\n";
    if(str[0]-'0'>= 0 && str[0]-'0'<SENSOR_COUNT){
        instance()->sensorMutex.lock();
        std::cout<<"GNE\n";
        std::cout<<instance()<<","<<instance_<<'\n';
        if(instance_->enabledSensors[str[0]-'0']==true){
            std::cout<<"Le capteur #"<<str[0]<<" est passé à l'état "<<str[2]<<'\n';
            instance_->sensorValues[str[0]-'0']=(str[2]-'0'!=0);
            if(str[2]-'0'==1){
>>>>>>> ea330ef516ee1e4666b9395788a6c1e01fb8d2aa
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
    instance_->sensorMutex.lock();
    instance_->enabledSensors[id]=true;
    if(instance_->sensorValues[id]) instance_->activeSensorsNum++;
    if(instance_->activeSensorsNum>1) Utils::AsservUtil::instance()->pause();
    instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::reset() {
    instance_->sensorMutex.lock();
    for(int i=0; i<SENSOR_COUNT; i++) { 
	instance_->enabledSensors[i] = false;
    }
    instance_->activeSensorsNum = 0;
    instance_->sensorMutex.unlock();
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
