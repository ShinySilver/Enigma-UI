#ifndef CUBE_LOAD_PROTOCOL
#define CUBE_LOAD_PROTOCOL 1

#include "../IA/protocol.hpp"
class IA;

class TestProtocol: public Protocol {
  public:
    TestProtocol(unsigned short p):priority{p}{};
    void update() override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority() override;
  private:
    unsigned char state = 0;
    unsigned short priority;
};

#endif
