#include "Settings.hpp"
#include "iostream"

namespace Utils{
  std::vector<Settings::DictionnaryEntry> Settings::dictionnary={};
  std::mutex Settings::dictionnaryMutex={};
  void (*Settings::cb_)() = {};

  /**
   * J'invite toute personne motivé à intégrer une hashmap dans le dico. Trop la flemme.
   */

  void Settings::setFlag(std::string flagName, unsigned char value) {
    dictionnaryMutex.lock();
    for (unsigned int i=0;i<dictionnary.size();i++) {
      if (dictionnary[i].id == flagName) {
        dictionnary[i].value = value;
        dictionnaryMutex.unlock();
        if(cb_) cb_();
        return;
      }
    }
    dictionnary.push_back({flagName, value});
    dictionnaryMutex.unlock();
    if(cb_) cb_();
  }

  short int Settings::getFlag(std::string flagName) { //return an unsigned char, or -1 if not found
    dictionnaryMutex.lock();
    for (auto entry : dictionnary) {
      if (entry.id == flagName) {
        dictionnaryMutex.unlock();
        return entry.value;
      }
    }
    dictionnaryMutex.unlock();
    return -1;
  }

  void Settings::setUpdateCallback(void (*callback)()){
    cb_ = callback;
  }
}
