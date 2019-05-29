#include <chrono>
#include <thread>
#include <iostream>

//#define PI
#ifdef PI
#include <wiringPi.h>
#else
#include "Utils/Starter.hpp"
#endif

#include "SFML/Graphics/Color.hpp"

#include "GUI/Window.hpp"
#include "GUI/Button.hpp"
#include "GUI/RotatingImage.hpp"
#include "GUI/Container.hpp"
#include "GUI/Displayer.hpp"
#include "GUI/Label.hpp"

#include "Utils/Settings.hpp"

#include "IA/ia.hpp"
#include "Protocols/testProtocol.hpp"

#include "Serial/SerialControl.hpp"

#include "Utils/sensorUtil.hpp"
#include "Utils/asservUtil.hpp"

#include "pinout.hpp"

GUI::Container &operator<<(GUI::Container &c1, GUI::Component *c2){c1.addComponent(c2);return c1;}

/**
 * Interface
 */
static GUI::Window *win = new GUI::Window("ENIgma UI", 800.0,480.0, -1);
static GUI::Container *mainMenu = new GUI::Container();
static GUI::Container *automaticModeMenu = new GUI::Container();
static GUI::Container *semiAutoModeMenu = new GUI::Container();
static AI::IA *ia = 0;

/**
 * Le serial et les modules
 */
static std::atomic<bool> listenerEnabled{};

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
  Utils::Settings::setFlag("isStarted",0);
  Utils::Settings::setFlag("protocolSelector",-1);
  Utils::Settings::setUpdateCallback([](){win->render();});

  /**
   * Init AI
   */
  ia = new AI::IA([](){
      Utils::AsservUtil::instance()->disable();
      Utils::SensorUtil::instance()->disable();
      std::cout<<"AI stopped.\n";
  },[](){
      std::cout<<"AI started.\n";
  });
  ia->addProtocol(new TestProtocol(1, 0, 0.0, "Ceci est un message envoyé par le protocole 1\n"));
  ia->addProtocol(new TestProtocol(0, 100, 0.0, "Ceci est un message envoyé par le protocole 2\n"));

  /**
   * Init main menu
   */
  GUI::Button btn1 {"Mode match", sf::Vector2f(400,230),sf::Vector2f(0,40), [](){win->setContent(automaticModeMenu);}};
  GUI::Button btn2 {"Mode manuel", sf::Vector2f(400,290),sf::Vector2f(0,40), [](){win->setContent(semiAutoModeMenu);}};
  *mainMenu<<bgImg<<title<<&btn1<<&btn2;

  /**
   * Init automaticModeMenu
   */
  GUI::Label label1 {"Parametrage:", sf::Vector2f(400,100)};
  std::string (*updater1)()  = []() -> std::string {return (Utils::Settings::getFlag("isLeftSide")?"Side: Left ":"Side: Right");};
  GUI::Displayer display1 {updater1, sf::Vector2f(400,160),sf::Vector2f(0,40),[](){Utils::Settings::setFlag("isLeftSide",!Utils::Settings::getFlag("isLeftSide"));}};
  GUI::Button btn5 {"PanicMode: True", sf::Vector2f(400,210),sf::Vector2f(0,40)};
  GUI::Label label2 {"Starter & Supervision:", sf::Vector2f(400,280)};
  std::string (*updater2)()  = []() -> std::string {if(Utils::Settings::getFlag("isStarted")){return "State: Launched";}else{return (Utils::Settings::getFlag("isStarterReady")?"Starter: Ready ":"Starter: NOT READY");}};
  GUI::Displayer display2 {updater2, sf::Vector2f(400,340),sf::Vector2f(0,40)};
  GUI::Button btn4 {">>", sf::Vector2f(735,50),sf::Vector2f(90,48), [](){win->setContent(mainMenu);}};
  *automaticModeMenu<<bgImg<<&btn4<<&btn5<<&display1<<&label1<<&label2<<&display2;


  /**
   * Init semiAutoModeMenu
   *///*
  GUI::Label label3 {"Selection protocole:", sf::Vector2f(400,100)};
  std::string (*updater3)()  = []() -> std::string {return "Courant: #"+std::to_string(Utils::Settings::getFlag("protocolSelector"));};
  GUI::Displayer display3 {updater3, sf::Vector2f(400,200),sf::Vector2f(0,40)};
  GUI::Button btn7 {"Executer", sf::Vector2f(400,250),sf::Vector2f(0,40), [](){ia->forceCurrentProtocol(Utils::Settings::getFlag("protocolSelector"));}};
  GUI::Button btn6 {"<<", sf::Vector2f(310,250),sf::Vector2f(0,40), [](){
      char s = (char)(Utils::Settings::getFlag("protocolSelector")-1);
      if(s<-1){
          s=(char)ia->getProtocolCount();
      }else if(s>=ia->getProtocolCount()){
          s=-1;
      }
      Utils::Settings::setFlag("protocolSelector", (unsigned char)s);
  }};
  GUI::Button btn8 {">>", sf::Vector2f(490,250),sf::Vector2f(0,40), [](){
      char s = (char)(Utils::Settings::getFlag("protocolSelector")+1);
      if(s<-1){
          s=(char)ia->getProtocolCount();
      }else if(s>=ia->getProtocolCount()){
          s=-1;
      }
      Utils::Settings::setFlag("protocolSelector", (unsigned char)s);
  }};
  GUI::Label label4 {"NB: Starter requis pour l'execution", sf::Vector2f(400,370)};
  *semiAutoModeMenu<<bgImg<<&label3<<&display3<<&btn4<<&btn6<<&btn7<<&btn8<<&label4;//*/

  /**
   * Init Window
   */
  win->setContent(mainMenu);

  /**
   * Init GPIO
   */
  #ifdef PI
  wiringPiSetupGpio();
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  pinMode(SIDE,INPUT);
  pinMode(STARTER,INPUT);
  #endif

  /**
   * Detection des périphériques
   */
  auto modules = SerialControl::listModules();

  /**
   * Initialisation des callbacks des modules
   */
  Utils::AsservUtil::instance();
  Utils::SensorUtil::instance();
  for(const auto &elem: modules) {
    if(elem->name=="SensorBoard"){
        std::cout<<"SensorBoard connectée\n";
        Utils::SensorUtil::instance()->setSerialModule(elem);
        Utils::SensorUtil::instance()->enable();
        elem->watch(Utils::SensorUtil::cb);
    }else if(elem->name=="MotionBase"){
        std::cout<<"MotionBase connectée\n";
        Utils::AsservUtil::instance()->setSerialModule(elem);
        Utils::AsservUtil::instance()->enable();
    }
  }

  /**
   * On lance le thread d'update
   */
  listenerEnabled=false;
  std::thread commandListener{[](){
      while(!listenerEnabled) std::this_thread::sleep_for(std::chrono::milliseconds(10));
      while(listenerEnabled){
          SerialControl::update();
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
  }};

  /**
   * Début du match
   */
  std::cout<<"Pour l'instant tout est ok...\n";
  #ifndef PI
  Utils::starter(STARTER);
  #else
  while(digitalRead(STARTER));
  std::cout<<"Starter prêt\n";
  Utils::Settings::setFlag("isStarterReady",1);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  while(!digitalRead(STARTER));
  std::cout<<"Robot lancé\n";
  Utils::Settings::setFlag("isStarted",1);
  #endif
  ia->enable();
  listenerEnabled=true;

  /**
   * Waiting for the window to close itself
   */
  win->join();
  std::cout << "Window joined.\n";
  ia->join();
  std::cout << "AI joined.\n";
  Utils::SensorUtil::instance()->disable();
  if(commandListener.joinable()){
      listenerEnabled=false;
      commandListener.join();
      std::cout<<"Serial joined!\n";
  }else{
      std::cout<<"Houston, nous avons un problème! Quelqu'un a réussi à faire crash le Serial!\n";
  }
  std::cout << "Normal end\n";
  return 0;
}
