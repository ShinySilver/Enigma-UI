#ifndef SENSOR_UTIL_H
#define SENSOR_UTIL_H

#include <thread>
#define SENSOR_COUNT 9

namespace SensorUtil{


    bool enabledSensors[SENSOR_COUNT]{false};
    std::mutex sensorsMutex{};

    // TODO enable disable

    void cb(const std::string& str){
        if((int)str[0]>= 0 && (int)str[0]<SENSOR_COUNT
                && enabledSensors[(int)str[0]]==true){
            std::cout<<"Le capteur #"<<str[0]<<" est passé à l'état "<<str[2]<<'\n';
        }else{
            std::cout<<"DEBUG "+str+"\n";
        }
    }
}

#endif /* end of include guard: SENSOR_MANAGER_H */
