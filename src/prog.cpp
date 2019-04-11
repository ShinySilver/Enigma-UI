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

static GUI::Window *win = new GUI::Window("ENIgma UI", 800.0,480.0);
static GUI::Container *mainMenu = new GUI::Container();
static GUI::Container *subMenu = new GUI::Container();

int main(void) {
  /**
   * Loading ressources
   */
  GUI::RotatingImage *bgImg = new GUI::RotatingImage("assets/textures/Aperture.png", 400, 240);
  GUI::Image *title = new GUI::Image("assets/textures/title.png", 400, 100);

  /**
   * Init main menu
   */
  GUI::Button btn1 {"Mode match", sf::Vector2f(400,220),sf::Vector2f(0,0), [](){win->setContent(subMenu);}};
  GUI::Button btn2 {"Mode protocole", sf::Vector2f(400,280)};
  GUI::Button btn3 {"Mode manuel", sf::Vector2f(400,340)};
  *mainMenu<<bgImg<<title<<&btn1<<&btn2<<&btn3;


  /**
   * Init submenu
   */
   GUI::Button btn4 {"->", sf::Vector2f(735,50),sf::Vector2f(90,48), [](){win->setContent(mainMenu);}};
  *subMenu<<bgImg<<&btn4;

  /**
   * Init Window
   */
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
