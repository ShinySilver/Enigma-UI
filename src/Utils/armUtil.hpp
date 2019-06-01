#ifndef ARM_UTIL
#define ARM_UTIL

#include "../Serial/SerialControl.hpp"

namespace Utils{
    class ArmUtil{
    private:
        static ArmUtil *instance_;
    public:
        SerialControl::Module *module{};
        static ArmUtil *instance();
    };
}

#endif /* end of include guard: ARM_UTIL */
