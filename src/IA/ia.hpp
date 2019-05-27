#ifndef IA_H
#define IA_H 1

#include "protocol.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>

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

      /**
       * Forcage du protocole courant
       */
      int getProtocolCount();
      int getCurrentProtocolId();
      void forceCurrentProtocol(int protocolId);

      /**
       * De quoi reset l'ia / les protocoles
       */
      //void restart();
      void reset(int protocolId);

      void join();

    private:
      std::vector<Protocol *> protocols_;
      std::atomic_int protocolCount_;
      std::atomic_int selectedProtocolId_{-1};
      std::mutex protocolIdMutex_;
      std::atomic_bool disabled_, enabled_, forced_;

      void (*onEnable_)();
      void (*onDisable_)();

      void update();
      std::thread mainLoop_;

      std::chrono::time_point<std::chrono::system_clock> matchStart_;

      void autoselectProtocol();
  };
}
#endif
