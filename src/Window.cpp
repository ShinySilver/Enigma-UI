#include <iostream>
#include <chrono>
#include <thread>

#include "Window.hpp"

namespace GUI {

  void Window::setContent(Component *c){
    winMutex.lock();
    contentPaneMutex.lock();
    contentPane_ = c;
    contentPaneMutex.unlock();
    winMutex.unlock();
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

  void Window::render(){
    auto next_frame = std::chrono::steady_clock::now();
    while(true){
       next_frame += std::chrono::milliseconds(1000/30); // 30 render per second

       winMutex.lock();
       if(!win_.isOpen()) return;
       win_.clear(bgColor_);
       contentPaneMutex.lock();
       if(contentPane_) contentPane_->render(this->win_);
       contentPaneMutex.unlock();
       win_.display();
       winMutex.unlock();

       std::this_thread::sleep_until(next_frame);
    }
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
      }
      contentPaneMutex.lock();
      if(contentPane_){
        //std::cout<<"Handling event...\n";
        for(auto l : contentPane_->getActionListeners()){
          l->actionPerformed(e);
        }
        //std::cout<<"Event handled!\n";
      }
      contentPaneMutex.unlock();
    }
  }

}
