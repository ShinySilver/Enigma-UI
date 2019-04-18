#ifndef IA_H
#define IA_H 1

#include "protocol.hpp"

#define MAX_PROTOCOL_NUMBER 15

#define PRIORITY_HIGHEST 6
#define PRIORITY_VERY_HIGH 5
#define PRIORITY_HIGH 4
#define PRIORITY_MEDIUM 3
#define PRIORITY_LOW 2
#define PRIORITY_VERY_LOW 1
#define PRIORITY_NULL 0

class IA {
  public:
    /**
     * Constructors
     */
    IA(Protocol *protocols[], short unsigned int protocolCount);
    IA();

    /**
     * Ajout d'un protocole créé de manière dynamique
     */
    void addProtocol(Protocol *protocol);

    /**
     * 'tick' de l'IA
     *  TODO: mettre ce tick dans un thread séparé
     */
    void update();

    /**
     * Activation/mise en pause de l'IA
     */
    void activate();
    void deactivate();

  private:
    Protocol *protocols_[MAX_PROTOCOL_NUMBER];
    unsigned short int protocolCount_;
    short int selectedProtocolId_=-1;
    void autoselectProtocol();
    bool active = false;
};
#endif
