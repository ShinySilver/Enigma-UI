#ifndef ASSERV_UTIL_H
#define ASSERV_UTIL_H 1

#include "Serial/SerialControl.hpp"

class Point {

    public :
        double x,y;

        std::string toString(){
            return std::to_string(x)+'~'+std::to_string(y);
        }

};

namespace AsservUtil {

namespace {

    std::atomic_bool isBusy_;
    SerialControl::Module *motionBase_;

}

inline std::atomic_bool *getIsBusy(){
    return &isBusy_;
}

inline void registerMotionBaseSerial(SerialControl::Module *module){
    motionBase_=module;
    motionBase_->watch([](const std::string& str){if(str=="movementFinished"){
        std::cout<<"MotionBase is now idle\n";
        isBusy_=false;
    }else{
        std::cout<<"Unrecognized command: "<<str<<'\n';
    }});
}

inline void forward(int distance){
    if(motionBase_){
        motionBase_->sendCommand("forward:"+std::to_string(distance)+";");
    }else{
        std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
    }
}

inline void rotate(double angle){
    if(motionBase_){
        motionBase_->sendCommand("rotate:"+std::to_string(angle)+";");
    }else{
        std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
    }
}

inline void move(std::vector<Point> checkpoints, double targetedAngle){
    if(motionBase_){
        std::string command = "move:";
        for(auto p:checkpoints){
            command+=p.toString()+",";
        }
        command+=std::to_string(targetedAngle);
        motionBase_->sendCommand(command+";");
    }else{
        std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
    }
}

} //namespace asservUtil


#endif
