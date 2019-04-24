#include "Settings.hpp"

namespace Utils{
  std::vector<Settings::DictionnaryEntry> Settings::dictionnary={};
  std::mutex Settings::dictionnaryMutex={};

  void Settings::setFlag(std::string flagName, unsigned char value) {
    dictionnaryMutex.lock();
    for (unsigned int i=0;i<dictionnary.size();i++) {
      if (dictionnary[i].id == flagName) {
        dictionnary[i].value = value;
        dictionnaryMutex.unlock();
        return;
      }
    }
    dictionnary.push_back({flagName, value});
    dictionnaryMutex.unlock();
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
}
