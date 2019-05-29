
#include "asservUtil.hpp"

namespace Utils{
    AsservUtil *AsservUtil::instance_ = 0;

    AsservUtil *AsservUtil::instance(){
        if(!instance_){
            instance_ = new AsservUtil;
            std::cout<<"creation d'une instance"<<'\n';
        }
        return instance_;
    }

    void AsservUtil::setSerialModule(SerialControl::Module *module){
        motionBase_=module;
        motionBase_->watch(this->cb);
    }

    void AsservUtil::cb(const std::string& str){
        if(str=="movementFinished"){
            std::cout<<"MotionBase is now idle\n";
            instance()->isBusy_=false;
        }else{
            std::cout<<"Unrecognized command: "<<str<<'\n';
        }
    }

    void AsservUtil::forward(int distance){
        if(motionBase_){
            motionBase_->sendCommand("forward:"+std::to_string(distance)+";");
        }else{
            std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
        }
    }

    void AsservUtil::rotate(double angle){
        if(motionBase_){
            motionBase_->sendCommand("rotate:"+std::to_string(angle)+";");
        }else{
            std::cout<<"Une commande a été envoyée à la MotionBase alors que la lib n'était pas initialisée\n";
        }
    }

    void AsservUtil::move(std::vector<Point> checkpoints, double targetedAngle){
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
}
