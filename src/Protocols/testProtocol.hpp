#ifndef CUBE_LOAD_PROTOCOL
#define CUBE_LOAD_PROTOCOL 1

#include "../IA/protocol.hpp"
#include <iostream>

class IA;

class TestProtocol: public Protocol {
  public:
    TestProtocol(unsigned short p, std::string t):priority_{p},text_{t}{};
    void update() override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority() override;
  private:
    unsigned short priority_;
    std::string text_;
};

#endif
