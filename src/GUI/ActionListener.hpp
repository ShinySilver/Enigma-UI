#ifndef ACTION_LISTENER
#define ACTION_LISTENER 1

#include "SFML/Graphics.hpp"

class ActionListener{
public:
  virtual void actionPerformed(sf::Event e) = 0;
};
#endif
