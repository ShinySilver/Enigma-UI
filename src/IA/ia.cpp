#include "ia.hpp"
#include "iostream"

namespace AI{

  IA::IA(void (*onDisable)(),void (*onEnable)()):
    protocols_{},
    protocolCount_{},
    disabled_{false},
    enabled_{false},
    onEnable_{onEnable},
    onDisable_{onDisable},
    mainLoop_{&IA::update, this} {

    }

  void IA::addProtocol(Protocol *protocol) {
    protocols_[protocolCount_++] = protocol;
  }

  void IA::autoselectProtocol() {
    selectedProtocolId_=-1;
    unsigned short int maxPriority = 0;
    for (unsigned short int selectedProtocolId = 0; selectedProtocolId < protocolCount_; ++selectedProtocolId) {
      if (!protocols_[selectedProtocolId]->isCompleted()) {
        if (protocols_[selectedProtocolId]->getPriority() > maxPriority
              && protocols_[selectedProtocolId]->getPriority()>PRIORITY_NULL) {
          maxPriority = protocols_[selectedProtocolId]->getPriority();
          selectedProtocolId_ = selectedProtocolId;
        }
      }
    }
  }

  void IA::update() {
    while (!disabled_) {
      /**
       * On attends le top départ
       */
      while(!enabled_){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }

      /**
       * Si on atteint la fin du match, l'ia s'arrête
       */
      if((std::chrono::duration<double>)(std::chrono::system_clock::now()-matchStart_)>std::chrono::seconds(100)){
        break;
      }
      if (selectedProtocolId_==-1||protocols_[selectedProtocolId_]->isCompleted()) {
        autoselectProtocol();
      }
      if(selectedProtocolId_!=-1)protocols_[selectedProtocolId_]->update();
    }
    if(onDisable_) onDisable_(); // Un callback pour couper les actionneurs=
  }

  void IA::enable(){
    enabled_=true;
    matchStart_=std::chrono::system_clock::now();
    if(onEnable_) onEnable_(); // Un callback pour activer les actionneurs
  }

  void IA::disable(){
    disabled_=true;
  }

  void IA::join(){
    if(mainLoop_.joinable()){
      std::cout<<"Waiting for the AI to finish...\n";
      mainLoop_.join();
      std::cout<<"AI thread joined.\n";
    }
  }
}
