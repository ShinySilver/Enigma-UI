#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>

#include "SFML/Graphics.hpp"

#include "ActionListener.hpp"

/**
 * Not for multithreaded use
 */
namespace GUI{
  class Component{
    public:
      Component():listeners{}{};
      virtual void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) = 0;
      void addActionListener(ActionListener *e) {listeners.emplace_back(e);}
      const std::vector<ActionListener *> *getActionListeners() {return &listeners;}
    private:
      std::vector<ActionListener *> listeners;
  };
}

#endif
