#include <iostream>
#include <chrono>
#include <thread>

#include "Window.hpp"

namespace GUI {

  void Window::setContent(Component *c){
    contentPaneMutex.lock();
    contentPane_ = c;
    std::cout<<"ContentPane Changed!\n";
    contentPaneMutex.unlock();
    //render();
  }

  void Window::close(){
    std::cout<<"Window closing... ";
    win_.close();
    std::cout<<"done\n";
  }

  void Window::join(){
    if(renderer_.joinable()){
      std::cout<<"Waiting for the display to close...\n";
      renderer_.join();
      std::cout<<"Display closed.\n";
    }
    if(eventHandler_.joinable()){
      std::cout<<"Waiting for the EventHandler to finish...\n";
      eventHandler_.join();
      std::cout<<"EventHandler closed.\n";
    }
  }

  void Window::renderLoop(){
    if(!animated_) return; // Si on désactive les animations, les rendus sont générés par les events
    auto next_frame = std::chrono::steady_clock::now();
    while(true){
      next_frame += std::chrono::milliseconds(1000/30); // 30 render per second
      if(!win_.isOpen()) return;
      render();
      std::this_thread::sleep_until(next_frame);
    }
  }

  void Window::render(){
    winMutex.lock();
    win_.clear(bgColor_);
    contentPaneMutex.lock();
    if(contentPane_)contentPane_->render(this->win_);
    contentPaneMutex.unlock();
    win_.display();
    winMutex.unlock();
  }

  void Window::handleEvent(){
    std::cout<<"Event handler started\n";
    sf::Event e;
    while(true){
      winMutex.lock();
      while(!win_.pollEvent(e)){
        winMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); // Up to 40 event per seconds
        winMutex.lock();
      }
      winMutex.unlock();
      if (e.type == sf::Event::Closed){
        close();
        return;
      }else if (e.type == sf::Event::MouseButtonReleased
                || e.type == sf::Event::TouchEnded){
        if(!animated_) render();
      }
      contentPaneMutex.lock();
      const std::vector<ActionListener *> *actionListeners;
      if(contentPane_){
        actionListeners = contentPane_->getActionListeners();
        contentPaneMutex.unlock();
        for(auto l : *actionListeners){
          l->actionPerformed(e);
        }
      }else{
        contentPaneMutex.unlock();
      }
    }
  }

}
