#ifndef PROTOCOL_H
#define PROTOCOL_H 1

class IA;

#include <string>
#include <vector>
#include <atomic>

class Protocol {
  public:
    virtual void update() = 0; //execute the next action of this protocol
    virtual bool isCompleted() = 0; //wether the last action of this protocol have already been executed or not
    virtual unsigned short int getPriority() = 0;
    inline void reset(){state_ = 0;}
  protected:
    std::atomic_int state_{0};
};
#endif
