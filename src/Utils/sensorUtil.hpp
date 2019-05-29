#ifndef SENSOR_UTIL_H
#define SENSOR_UTIL_H

#define SENSOR_COUNT 9
#define FRONT_LEFT_SENSOR 0
#define FRONT_RIGHT_SENSOR 0
#define LEFT_FRONT_SENSOR 0
#define LEFT_RIGHT_SENSOR 0

#include <thread>
#include <mutex>
#include "asservUtil.hpp"

namespace Utils{
    class SensorUtil{
    private:
        bool enabledSensors[SENSOR_COUNT]{false};
        bool sensorValues[SENSOR_COUNT]{false};
        int activeSensorsNum = 0;
        std::mutex sensorMutex{};
        static SensorUtil *instance_;
        SerialControl::Module *module_{};
    public:
        static SensorUtil *instance();

        inline void setSerialModule(SerialControl::Module *module){module_=module;}
        static void cb(const std::string& str);
        inline void reset(){for(int i=0;i<SENSOR_COUNT;i++)enabledSensors[i]=false;activeSensorsNum=0;}
        void enableSensor(int id);
        inline void disable(){module_->sendCommand("deactivate;");}
        inline void enable(){module_->sendCommand("activate;");module_->sendCommand("dsensors;");}
    };
}
#endif /* end of include guard: SENSOR_MANAGER_H */
