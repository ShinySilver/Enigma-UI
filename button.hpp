#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "component.hpp"
#include "iostream"

#define FONT "arialbd.ttf"

namespace GUI{
  class Button : public Component, private ActionListener{

    public:
      Button(std::string text, sf::Color bgColor, sf::Vector2f pos, sf::Vector2f size, std::string fontPath= "arialbd.ttf"):
        bgColor_{bgColor},pos_{pos}, size_{size}, rectangle_{size}{
        // TODO: faire un gestionnaire des polices
        if(!font_.loadFromFile(fontPath))      throw std::runtime_error("Could not find font at " + fontPath);
        text_ = sf::Text{text, font_};
        sprite_->setPosition(pos_.x, pos_.y);
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        if(sprite_) target.draw(*sprite_, states);
      }

      bool contains(int posX, int posY){
        return posX<pos_.x+size_.x/2.0 && posX>pos_.x-size_.x/2.0
               && posY<pos_.y+size_.y/2.0 && posY>pos_.y-size_.y/2.0;
      }

      void setIcon(sf::Texture *texture){
        auto size = texture->getSize();
        sprite_->setTexture(*texture);
        sprite_->setOrigin((float)size.x/2,(float)size.y/2);
      }

    private:
      sf::Text text_;
      sf::Sprite *sprite_;
      sf::Color bgColor_;
      sf::Vector2f pos_, size_;
      sf::RectangleShape rectangle_;
      sf::Font font_;

  };
}
#endif /* end of include guard: IMAGE_HPP */
