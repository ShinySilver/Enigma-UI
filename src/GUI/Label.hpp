#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>
#include <functional>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Component.hpp"


namespace GUI{
  class Label : public Component{

    public:
      Label(std::string text, sf::Vector2f pos,
          const sf::Color textColor = sf::Color::Black,
          std::string fontPath= "assets/fonts/arialbd.ttf"):
              pos_{pos}{
        // TODO: faire un gestionnaire des polices
        if(!font_.loadFromFile(fontPath))      throw std::runtime_error("Could not find font at " + fontPath);
        text_ = sf::Text{text, font_};
        sf::FloatRect textRect = text_.getLocalBounds();
        text_.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        text_.setPosition(pos_.x, pos_.y);
        text_.setFillColor(textColor);
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        target.draw(text_, states);
      }

    private:
      sf::Text text_;
      sf::Vector2f pos_;
      sf::Font font_;

  };
}
#endif /* end of include guard: IMAGE_HPP */
