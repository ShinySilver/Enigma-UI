#include "armUtil.hpp"

#include <iostream>

namespace Utils{
    ArmUtil *ArmUtil::instance_ = 0;

    ArmUtil *ArmUtil::instance(){
        if(!instance_){
            instance_ = new ArmUtil;
            #ifdef DEBUG
            std::cout << "Instance de ArmUtil créée\n";
            #endif
        }
        return instance_;
    }
}
