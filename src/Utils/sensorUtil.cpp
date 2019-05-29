#include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
    std::cout<<"sensor #"<<str[0]-'0'<<" passe à "<<str[2]-'0'<<"\n";
    if(str[0]-'0'>= 0 && str[0]-'0'<SENSOR_COUNT){
        instance()->sensorMutex.lock();
        std::cout<<"GNE\n";
        std::cout<<instance()<<","<<instance_<<'\n';
        if(instance_->enabledSensors[str[0]-'0']==true){
            std::cout<<"Le capteur #"<<str[0]<<" est passé à l'état "<<str[2]<<'\n';
            instance_->sensorValues[str[0]-'0']=(str[2]-'0'!=0);
            if(str[2]-'0'==1){
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
