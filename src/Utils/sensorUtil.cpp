 #include "sensorUtil.hpp"

Utils::SensorUtil *Utils::SensorUtil::instance_=0;

void Utils::SensorUtil::cb(const std::string& str){
    const int id = str[0]-'0';
    const bool value = str[2]-'0';
    if(bool(id>= 0) && bool(id<SENSOR_COUNT)){
	instance_->sensorMutex.lock();
        if(instance_->enabledSensors[id]){
            std::cout<<"Le capteur #"<<id<<" est passé à l'état "<<value<<'\n';
            instance_->sensorValues[id]=value;
	    if(instance_->hasDetected()){
	        std::cout << "pause\n";
                Utils::AsservUtil::instance()->pause();
            }else {
    		std::cout << "resume\n";
                Utils::AsservUtil::instance()->resume();
            }
        }
        instance_->sensorMutex.unlock();
    }
    #ifdef DEBUG
    std::cout << "DEBUG SENSORS: " << str << "\n";
    #endif
}

bool Utils::SensorUtil::hasDetected(){
    for(int i=0; i<SENSOR_COUNT; i++) {
	if(instance_->enabledSensors[i]) {
	    if(instance_->sensorValues[i]) {
		return true;
	    }
	}
    }
    return false;
}

void Utils::SensorUtil::enableSensor(int id){
    instance()->sensorMutex.lock();
    instance_->enabledSensors[id]=true;
    if(instance_->hasDetected()) Utils::AsservUtil::instance()->pause();
    instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::reset() {
    instance()->sensorMutex.lock();
    for(int i=0; i<SENSOR_COUNT; i++) {
	instance_->enabledSensors[i] = false;
        instance_->sensorValues[i] = false;
    }
    if(instance_->module_) instance_->module_->sendCommand("dsensors;");
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
