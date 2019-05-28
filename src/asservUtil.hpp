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

    namespace {
        std::atomic_bool isBusy;
        SerialControl::Module *motionBase;
    }

    inline std::atomic_bool *getIsBusy(){return &isBusy;}

    inline void setModule(SerialControl::Module *mb){motionBase=mb;}

    inline void forward(int distance){
        if(motionBase){
            motionBase->sendCommand("forward:"+std::to_string(distance)+";");
        }else{
            std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
        }
    }

    inline void rotate(double angle){
        if(motionBase){
            motionBase->sendCommand("rotate:"+std::to_string(angle)+";");
        }else{
            std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
        }
    }

    inline void move(std::vector<Point> checkpoints, double targetedAngle){
        if(motionBase){
            std::string command = "move:";
            for(auto p:checkpoints){
                command+=p.toString()+",";
            }
            command+=std::to_string(targetedAngle);
            motionBase->sendCommand(command+";");
        }else{
            std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
        }
    }

    inline void cb(const std::string& str){
        if(str=="movementFinished"){
            std::cout<<"MotionBase is now idle\n";
            isBusy=false;
        }else{
            std::cout<<"Unrecognized command: "<<str<<'\n';
        }
    }
}

#endif
