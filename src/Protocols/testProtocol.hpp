#ifndef CUBE_LOAD_PROTOCOL
#define CUBE_LOAD_PROTOCOL 1

#include "../IA/protocol.hpp"
#include <iostream>

class IA;

class TestProtocol: public Protocol {
  public:
    TestProtocol(unsigned short p, int t, double a, std::string txt):priority_{p},translation_{t},angle_{a},text_{txt}{};
    void update() override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority() override;
  private:
    unsigned short priority_;
    int translation_;
    double angle_;
    std::string text_;
};

#endif
