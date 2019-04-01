#ifndef ROTATING_IMAGE_HPP
#define ROTATING_IMAGE_HPP

#include <string.h>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "component.hpp"
#include "image.hpp"

namespace GUI{
  class RotatingImage : public Image{
    public:
      RotatingImage(std::string path, float posX, float posY):Image{path,posX,posY}{};

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        sprite_.rotate(360/30/10);
        target.draw(sprite_, states);
      }
  };
}
#endif /* end of include guard: IMAGE_HPP */
