#include <chrono>
#include <thread>
#include <iostream>

#include "SFML/Graphics/Color.hpp"

#include "Window.hpp"
#include "Button.hpp"
#include "RotatingImage.hpp"
#include "Container.hpp"

#define DEBUG 1

GUI::Container& operator<<(GUI::Container &c1, GUI::Component *c2){c1.addComponent(c2);return c1;}

static GUI::Window *win;

static GUI::Container *subMenu=[](){
  GUI::Container *c = new GUI::Container();
  GUI::RotatingImage *bgImg = new GUI::RotatingImage("assets/textures/Aperture.png", 400, 240);
  *c<<bgImg;
  return c;
}();

static GUI::Container *mainMenu=[](){
  GUI::Container *c = new GUI::Container();
  GUI::RotatingImage *bgImg = new GUI::RotatingImage("assets/textures/Aperture.png", 400, 240);
  GUI::Image *title = new GUI::Image("assets/textures/title.png", 400, 100);
  GUI::Button *btn1 = new GUI::Button("Mode match", sf::Vector2f(400,220),sf::Vector2f(0,0), sf::Color::White, sf::Color::Black, *[](){std::cout<<"blbl\n";win->setContent(subMenu);std::cout<<"Menu changé!\n";});
  GUI::Button *btn2 = new GUI::Button("Mode protocole", sf::Vector2f(400,280));
  GUI::Button *btn3 = new GUI::Button("Mode manuel", sf::Vector2f(400,340));
  *c<<bgImg<<title<<btn1<<btn2<<btn3;
  return c;
}();

int main(void) {
  win = new GUI::Window("ENIgma UI", 800.0,480.0);
  win->setContent(mainMenu);

  win->join();
  std::cout << "Normal end\n";
  return 0;
}

/*static sf::Texture loadTextureFromFile(std::string path){
  sf::Texture texture;
  if (!texture.loadFromFile(path))   throw std::runtime_error("Could not find texture at " + path);
  texture.setSmooth(true);
  std::cout << "Loaded texture : '" << path << "'\n";
  return texture;
}*/
