#ifndef PROTOCOL_H
#define PROTOCOL_H 1

class IA;

#include <string>
#include <vector>

class Protocol {
  public:
    virtual void update() = 0; //execute the next action of this protocol
    virtual bool isCompleted() = 0; //wether the last action of this protocol have already been executed or not
    virtual unsigned short int getPriority() = 0;
};
#endif
