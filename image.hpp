#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string.h>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "component.hpp"
#include "iostream"

namespace GUI{
  class Image : public Component{
    public:
      Image(std::string path, float posX, float posY):x_{posX}, y_{posY} {
        if (!texture_.loadFromFile(path)){
          throw std::runtime_error("Could not find texture at " + path);
        }
        texture_.setSmooth(true);
        texture_.setRepeated(true);
        auto size = texture_.getSize();
        sprite_.setTexture(texture_);
        sprite_.setOrigin((float)size.x/2,(float)size.y/2);
        sprite_.setPosition(sf::Vector2f(posX, posY));
        std::cout << "Loaded texture : '" << path << "'\n";
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        sprite_.rotate(360/90);
        target.draw(sprite_, states);
      }

    private:
        sf::Texture texture_;
        sf::Sprite sprite_;
        float x_, y_;
  };
}
#endif /* end of include guard: IMAGE_HPP */
