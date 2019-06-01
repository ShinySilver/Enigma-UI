#ifndef DISPLAYER_HPP
#define DISPLAYER_HPP

#include <string>
#include <functional>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Component.hpp"


namespace GUI{
  class Displayer : public Component, private ActionListener{

    public:
      Displayer(std::string (*textRef)(), sf::Vector2f pos,
          sf::Vector2f size = sf::Vector2f(0,0),
          void (*cb)() = 0,
          const sf::Color borderColor=sf::Color::White,
          const sf::Color fgColor=sf::Color::Black,
          const sf::Color textColor = sf::Color::Black,
          std::string fontPath= "assets/fonts/arialbd.ttf"):
              pos_{pos}, textRef_{textRef}, cb_{cb}{
        // TODO: faire un gestionnaire des polices
        if(!font_.loadFromFile(fontPath))      throw std::runtime_error("Could not find font at " + fontPath);
        text_ = sf::Text{textRef_(), font_};
        sf::FloatRect textRect = text_.getLocalBounds();
        text_.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        text_.setPosition(pos_.x, pos_.y);
        text_.setFillColor(textColor);

        size.x=std::max(size.x,textRect.width+16);
        size.y=std::max(size.y,textRect.height+8);

        rectangle_ = sf::RectangleShape(size);
        rectangle_.setOrigin(size.x/2, size.y/2);
        rectangle_.setPosition(pos_.x, pos_.y);
        rectangle_.setFillColor(borderColor);

        size+={2,2};
        border_ = sf::RectangleShape(size);
        border_.setOrigin(size.x/2, size.y/2);
        border_.setPosition(pos_.x, pos_.y);
        border_.setFillColor(fgColor);

        size_=size;
        this->addActionListener(this);
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        text_.setString(textRef_());
        target.draw(border_, states);
        target.draw(rectangle_, states);
        target.draw(text_, states);
      }

      inline bool contains(int posX, int posY){
        return posX<pos_.x+size_.x/2.0 && posX>pos_.x-size_.x/2.0
               && posY<pos_.y+size_.y/2.0 && posY>pos_.y-size_.y/2.0;
      }

      void actionPerformed(sf::Event e) override{
        //std::cout<<"Event transmitted to button!\n";
        if(e.type == sf::Event::MouseButtonPressed){
          //std::cout<<"MouseButtonEvent transmitted to button!\n";
          if (this->contains(e.mouseButton.x, e.mouseButton.y)){
            //std::cout<<"Button pressed!\n";
            if(cb_) cb_();
          }
        }
      }

    private:
      sf::Text text_;
      sf::Vector2f pos_, size_;
      sf::RectangleShape rectangle_, border_;
      sf::Font font_;
      std::string (*textRef_)();
      void (*cb_)();

  };
}
#endif /* end of include guard: IMAGE_HPP */
