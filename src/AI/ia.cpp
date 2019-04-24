#include "ia.hpp"

IA::IA():
  protocols_{},
  protocolCount_{}{}

IA::IA(Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount}{
  for (unsigned short int i = 0; i < protocolCount; ++i) {
    protocols_[i] = protocols[i];
  }
}

void IA::addProtocol(Protocol *protocol) {
  protocols_[protocolCount_++] = protocol;
}

void IA::autoselectProtocol() {
  selectedProtocolId_=-1;
  unsigned short int maxPriority = 0;
  for (unsigned short int selectedProtocolId = 0; selectedProtocolId < protocolCount_; ++selectedProtocolId) {
    if (!protocols_[selectedProtocolId]->isCompleted()) {
      if (protocols_[selectedProtocolId]->getPriority(this) > maxPriority
            && protocols_[selectedProtocolId]->getPriority(this)>PRIORITY_NULL) {
        maxPriority = protocols_[selectedProtocolId]->getPriority(this);
        selectedProtocolId_ = selectedProtocolId;
      }
    }
  }
}

void IA::update() {
  if(!active)return;
  if (/*isBusy()*/true) { // #############################
    if (selectedProtocolId_==-1||protocols_[selectedProtocolId_]->isCompleted()) {
      autoselectProtocol();
    }
    if(selectedProtocolId_!=-1)protocols_[selectedProtocolId_]->update(this);
  }
}

void IA::activate(){
  active=true;
  //Serial.println("LOG activated_AI");
}
void IA::deactivate(){
  active=false;
  //Serial.println("LOG deactivated_AI");
}
