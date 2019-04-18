#include "Settings.hpp"

#include <string>

namespace Utils{
  std::vector<Settings::DictionnaryEntry> Settings::dictionnary={};

  void Settings::setFlag(std::string flagName, unsigned char value) {
    for (unsigned int i=0;i<dictionnary.size();i++) {
      if (dictionnary[i].id == flagName) {
        dictionnary[i].value = value;
        return;
      }
    }
    dictionnary.push_back({flagName, value});
  }

  short int Settings::getFlag(std::string flagName) { //return an unsigned char, or -1 if not found
    for (auto entry : dictionnary) {
      if (entry.id == flagName) {
        return entry.value;
      }
    }
    return -1;
  }
}
