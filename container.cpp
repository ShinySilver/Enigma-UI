#include "container.hpp"
#include "component.hpp"

namespace GUI{
  void Container::render(sf::RenderTarget& target, sf::RenderStates states){
    for (auto i: components)
      i->render(target, states);
  }

  void Container::addComponent(Component *c){
    components.emplace_back(c);
  }
}
