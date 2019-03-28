#include <chrono>
#include <thread>
#include <iostream>

#include "window.hpp"
#include "button.hpp"
#include "image.hpp"
#include "container.hpp"

#define DEBUG 1

int main(void) {
  GUI::Window win{"ENIgma UI", 800.0,480.0};
  GUI::Container c{};
  GUI::Image img{"sphere.png", 400, 240};
  c.addComponent(&img);
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
