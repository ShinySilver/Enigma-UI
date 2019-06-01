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

void Utils::SensorUtil::enableSensor(int id){
    instance()->sensorMutex.lock();
    
	instance_->enabledSensors[id]=true;
   	if(instance_->sensorValues[id]) Utils::AsservUtil::instance()->pause();
    
	instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::disableSensor(int id){
	instance()->sensorMutex.lock();

	instance_->enabledSensors[id] = false;

	instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::reset() {
    instance()->sensorMutex.lock();

    for(int i=0; i<SENSOR_COUNT; i++) {
		instance_->enabledSensors[i] = false;
        instance_->sensorValues[i] = false;
    }
    if(instance_->module_) {
		instance_->initValues();
		std::cout << "reseted sensors\n";
	}
    
	instance_->sensorMutex.unlock();
}

void Utils::SensorUtil::enable() {
	instance()->module_->sendCommand("activate;");
	instance_->initValues();
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


//----private functions
//these function have no mutex, so you must only use them
//in a function with is already thread-safe

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

void Utils::SensorUtil::initValues() {
	const std::string sensors = instance()->module_->sendCommand("dsensors;");
	std::cout << "dsensors; returned : " << sensors << "\n";
	for(int i=0; i<SENSOR_COUNT; i++){
		sensorValues[i]=sensors[i]-'0';
	}
}

