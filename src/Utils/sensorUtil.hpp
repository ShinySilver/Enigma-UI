#ifndef SENSOR_UTIL_H
#define SENSOR_UTIL_H

#define SENSOR_COUNT 9
#define FRONT_LEFT_SENSOR 0
#define FRONT_RIGHT_SENSOR 4
#define LEFT_FRONT_SENSOR 3
#define RIGHT_FRONT_SENSOR 8
#define LEFT_BACK_SENSOR 1
#define RIGHT_BACK_SENSOR 6
#define BACK_LEFT_SENSOR 2
#define BACK_RIGHT_SENSOR 7
#define EXTRA_SENSOR 5

#include <thread>
#include <mutex>
#include "asservUtil.hpp"

namespace Utils{
    class SensorUtil{
    private:
        bool enabledSensors[SENSOR_COUNT]{false};
        bool sensorValues[SENSOR_COUNT]{true};
        std::mutex sensorMutex{};
        static SensorUtil *instance_;
        SerialControl::Module *module_{};
		bool hasDetected();
		void initValues();
    public:
        static SensorUtil *instance();

        inline void setSerialModule(SerialControl::Module *module){
            module_=module;
            module_->watch(this->cb);
        }
        static void cb(const std::string& str);
        void reset();
        void enableSensor(int id);
		void disableSensor(int id);
        void enable();

        inline void disable(){module_->sendCommand("deactivate;");}
    };
}
#endif /* end of include guard: SENSOR_MANAGER_H */
