#include "Container.hpp"
#include "Component.hpp"

namespace GUI{
  void Container::render(sf::RenderTarget& target, sf::RenderStates states){
    for (auto i: components_)
      i->render(target, states);
  }

  void Container::addComponent(Component *c){
    components_.emplace_back(c);
  }
}
