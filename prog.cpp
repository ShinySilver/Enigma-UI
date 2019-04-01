#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics/Color.hpp>

#include "window.hpp"
#include "button.hpp"
#include "rotatingImage.hpp"
#include "container.hpp"

#define DEBUG 1

int main(void) {
  GUI::Window win{"ENIgma UI", 800.0,480.0};
  GUI::Container c{};
  GUI::RotatingImage bgImg{"assets/textures/Aperture.png", 400, 240};
  GUI::Image title{"assets/textures/title.png", 400, 100};
  GUI::Button btn1{"Mode match", sf::Vector2f(400,220)};
  GUI::Button btn2{"Mode protocole", sf::Vector2f(400,280)};
  GUI::Button btn3{"Mode manuel", sf::Vector2f(400,340)};
  c.addComponent(&bgImg);
  c.addComponent(&title);
  c.addComponent(&btn1);
  c.addComponent(&btn2);
  c.addComponent(&btn3);
  win.setContent(&c);


  win.join();
  std::cout << "Normal end\n";
  return 0;
}

static sf::Texture loadTextureFromFile(std::string path){
  sf::Texture texture;
  if (!texture.loadFromFile(path))   throw std::runtime_error("Could not find texture at " + path);
  texture.setSmooth(true);
  std::cout << "Loaded texture : '" << path << "'\n";
  return texture;
}
