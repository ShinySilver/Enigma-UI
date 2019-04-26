#ifndef IA_H
#define IA_H 1

#include "protocol.hpp"

#include <thread>
#include <atomic>
#include <chrono>

#define MAX_PROTOCOL_NUMBER 15

#define PRIORITY_HIGHEST 6
#define PRIORITY_VERY_HIGH 5
#define PRIORITY_HIGH 4
#define PRIORITY_MEDIUM 3
#define PRIORITY_LOW 2
#define PRIORITY_VERY_LOW 1
#define PRIORITY_NULL 0

namespace AI{
  class IA {
    public:
      /**
       * Constructors
       */
      IA(void (*onEnable)()=0,void (*onDisable)()=0);

      /**
       * Ajout d'un protocole créé de manière dynamique
       */
      void addProtocol(Protocol *protocol);

      /**
       * Activation/mise en pause de l'IA
       */
      void enable();
      void disable();

      void join();

    private:
      Protocol *protocols_[MAX_PROTOCOL_NUMBER];
      unsigned short int protocolCount_;
      short int selectedProtocolId_=-1;
      std::atomic_bool disabled_, enabled_;

      void (*onEnable_)();
      void (*onDisable_)();

      void update();
      std::thread mainLoop_;

      std::chrono::time_point<std::chrono::system_clock> matchStart_;

      void autoselectProtocol();
  };
}
#endif
