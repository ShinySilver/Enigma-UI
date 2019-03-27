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
      Button(std::string text, sf::Color bgColor, float posX, float posY, std::string fontPath= "arialbd.ttf"):bgColor_{bgColor},x_{posX}, y_{posY} {
        if(!font_.loadFromFile(fontPath))      throw std::runtime_error("Could not find font at " + fontPath);
        text_ = sf::Text{text, font_};
      }

      Button(std::string text, std::string iconPath, float posX, float posY, std::string fontPath= "arialbd.ttf"):x_{posX}, y_{posY} {
        if(!font_.loadFromFile(fontPath))      throw std::runtime_error("Could not find font at " + fontPath);
        text_= sf::Text{text, font_};

        if (!texture_.loadFromFile(iconPath))   throw std::runtime_error("Could not find texture at " + iconPath);
        texture_.setSmooth(true);
        //texture_.setRepeated(true);
        auto size = texture_.getSize();
        sprite_.setTexture(texture_);
        sprite_.setOrigin((float)size.x/2,(float)size.y/2);
        sprite_.setPosition(sf::Vector2f(posX, posY));
        std::cout << "Loaded texture : '" << iconPath << "'\n";
      }

      void render(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) override{
        target.draw(sprite_, states);
      }

      bool contains(int posX, int posY){
        return true;
      }

    private:
      sf::Text text_;
      sf::Texture texture_;
      sf::Sprite sprite_;
      sf::Color bgColor_;
      float x_, y_;
      sf::RectangleShape rectangle;
      sf::Font font_;

  };
}
#endif /* end of include guard: IMAGE_HPP */
