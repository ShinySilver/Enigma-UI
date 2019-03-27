#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include "component.hpp"
#include "SFML/Graphics.hpp"


namespace GUI{
  class Container : public Component, ActionListener{
    public:
      Container():components{}{}

      /**
       * Rajoute un élément graphique au container
       */
      void addComponent(Component *c);

      // From component
      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override;

      // ActionListener
      void actionPerformed(sf::Event event) override {
        for_each(getActionListeners().begin(), getActionListeners().end(), [&](ActionListener *a){a->actionPerformed(event);});
      }

    private:
      std::vector<Component*> components;
  };
}
#endif
