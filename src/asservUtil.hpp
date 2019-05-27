#ifndef ASSERV_UTIL_H
#define ASSERV_UTIL_H

#include "Serial/SerialControl.hpp"

#include <thread>

typedef struct {double x,y;} Point;

namespace AsservUtil{
    std::atomic_bool isBusy{false};
    SerialControl::Module *motionBase=0;

    void forward(int distance){
        if(motionBase){
            motionBase->sendCommand("forward:"+distance);
        }else{
            std::cout<<"Le module motionBase n'a pas été chargé!\n";
        }
    }
    void rotate(double angle);
    void move(Point checkpoints[], int checkpointAmount, double targetedAngle);

    void cb(const std::string& str){
        if(str=="movementFinished"){
            std::cout<<"MotionBase is now idle\n";
            isBusy=false;
        }else{
            std::cout<<"Unrecognized command: "<<str<<'\n';
        }
    }
}

#endif /* end of include guard: SENSOR_MANAGER_H */
