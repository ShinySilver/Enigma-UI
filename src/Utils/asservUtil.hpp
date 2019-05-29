#ifndef ASSERV_UTIL_H
#define ASSERV_UTIL_H 1

#include "../Serial/SerialControl.hpp"

#include <iostream>
#include <atomic>

class Point {

    public :
        double x,y;

        std::string toString(){
            return std::to_string(x)+'~'+std::to_string(y);
        }

};

namespace Utils{
    class AsservUtil {
        public:
            static AsservUtil *instance();

            /**
             * Wether l'asserv est arrivé à destination or not
             */
            inline bool isBusy() const{return isBusy_;}

            /**
             * Link de l'utilitaire de controle et du module Serial
             */
            void setSerialModule(SerialControl::Module *module);

            /**
             * Les commandes de mouvement. All-encompassing (lol)
             * Il faut penser à set le module serial, sinon ça marche pas.
             */
            void forward(int distance);
            void rotate(double angle);
            void move(std::vector<Point> checkpoints, double targetedAngle);
            void pause();
            void resume();
            inline void disable(){motionBase_->sendCommand("deactivate;");}
            inline void enable(){motionBase_->sendCommand("activate;");}
        private:
            static AsservUtil *instance_;
            std::atomic_bool isBusy_;
            SerialControl::Module *motionBase_;

            static void cb(const std::string& str);
    };
} //namespace asservUtil


#endif
