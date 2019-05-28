#ifndef ASSERV_UTIL_H
#define ASSERV_UTIL_H 1

#include "Serial/SerialControl.hpp"

typedef struct {
    double x,y;
    std::string toString(){
        return std::to_string(x)+'~'+std::to_string(y);
    }
} Point;

namespace AsservUtil{

    static std::atomic_bool isBusy{false};
    static SerialControl::Module *motionBase{0};

    static inline void forward(int distance){
        if(motionBase){
            motionBase->sendCommand("forward:"+std::to_string(distance));
        }
    }

    static inline void rotate(double angle){
        if(motionBase){
            motionBase->sendCommand("rotate:"+std::to_string(angle));
        }
    }

    static inline void move(std::vector<Point> checkpoints, double targetedAngle){
        if(motionBase){
            std::string command = "move:";
            for(auto p:checkpoints){
                command+=p.toString()+",";
            }
            command+=std::to_string(targetedAngle);
            motionBase->sendCommand(command);
        }
    }

    static inline void cb(const std::string& str){
        if(str=="movementFinished"){
            std::cout<<"MotionBase is now idle\n";
            isBusy=false;
        }else{
            std::cout<<"Unrecognized command: "<<str<<'\n';
        }
    }
}

#endif
