#include <chrono>
#include <thread>
#include <iostream>

#include "SFML/Graphics/Color.hpp"

#include "GUI/Window.hpp"
#include "GUI/Button.hpp"
#include "GUI/RotatingImage.hpp"
#include "GUI/Container.hpp"
#include "GUI/Displayer.hpp"
#include "GUI/Label.hpp"

#include "Utils/Settings.hpp"

#define DEBUG 1

GUI::Container& operator<<(GUI::Container &c1, GUI::Component *c2){c1.addComponent(c2);return c1;}

static GUI::Window *win = new GUI::Window("ENIgma UI", 800.0,480.0, false);
static GUI::Container *mainMenu = new GUI::Container();
static GUI::Container *subMenu = new GUI::Container();

int main(void) {
  /**
   * Loading ressources
   */
  GUI::Image *bgImg = new GUI::Image("assets/textures/Aperture.png", 400, 240);
  GUI::Image *title = new GUI::Image("assets/textures/title.png", 400, 100);

  /**
   * Settings
   */
  Utils::Settings::setFlag("isLeftSide",0);
  Utils::Settings::setFlag("maxPwm",0);
  Utils::Settings::setFlag("isStarterReady",0);


  /**
   * Init main menu
   */
  GUI::Button btn1 {"Mode match", sf::Vector2f(400,220),sf::Vector2f(0,40), [](){win->setContent(subMenu);}};
  GUI::Button btn2 {"Mode protocole", sf::Vector2f(400,280),sf::Vector2f(0,40)};
  GUI::Button btn3 {"Mode manuel", sf::Vector2f(400,340),sf::Vector2f(0,40)};
  *mainMenu<<bgImg<<title<<&btn1<<&btn2<<&btn3;


  /**
   * Init submenu
   */
  GUI::Label label1 {"Parametrage:", sf::Vector2f(400,100)};
  std::string (*updater1)()  = []() -> std::string {return (Utils::Settings::getFlag("isLeftSide")?"Side: Left ":"Side: Right");};
  GUI::Displayer display1 {updater1, sf::Vector2f(400,160),sf::Vector2f(0,40),[](){Utils::Settings::setFlag("isLeftSide",!Utils::Settings::getFlag("isLeftSide"));}};
  GUI::Button btn5 {"LM_Ready: False", sf::Vector2f(400,210),sf::Vector2f(0,40)};

  GUI::Label label2 {"Starter & Supervision:", sf::Vector2f(400,280)};
  std::string (*updater2)()  = []() -> std::string {return (Utils::Settings::getFlag("isStarterReady")?"Starter: Ready ":"Starter: NOT READY");};
  GUI::Displayer display2 {updater2, sf::Vector2f(400,340),sf::Vector2f(0,40);

  GUI::Button btn4 {">>", sf::Vector2f(735,50),sf::Vector2f(90,48), [](){win->setContent(mainMenu);}};
  *subMenu<<bgImg<<&btn4<<&btn5<<&display1<<&label1<<&label2<<&display2;

  /**
   * Init AI
   */


  /**
   * Init Window
   */
  win->setContent(mainMenu);
  win->join();
  std::cout << "Normal end\n";
  return 0;
}
