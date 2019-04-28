#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string.h>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Component.hpp"

namespace GUI{
  class Image : public Component{
    public:
      Image(std::string path, float posX, float posY):x_{posX}, y_{posY} {
        if (!texture_.loadFromFile(path)){
          throw std::runtime_error("Could not find texture at " + path);
        }
        #ifndef DESKTOP
        std::this_thread::sleep_for(std::chrono::seconds(5)); // un délai pour le chargement de l'image
        #endif
        texture_.setSmooth(true);
        texture_.setRepeated(true);
        auto size = texture_.getSize();
        sprite_.setTexture(texture_);
        sprite_.setOrigin((float)size.x/2,(float)size.y/2);
        sprite_.setPosition(sf::Vector2f(posX, posY));
        std::cout << "Loaded texture : '" << path << "'\n";
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        target.draw(sprite_, states);
      }

    private:
        sf::Texture texture_;
        float x_, y_;

    protected:
      sf::Sprite sprite_;
  };
}
#endif /* end of include guard: IMAGE_HPP */
