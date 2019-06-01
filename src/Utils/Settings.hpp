#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <string>
#include <mutex>

namespace Utils{
  class Settings{ // static class. Yeah.
    public:
      static void setFlag(std::string flagName, char value);
      static char getFlag(std::string flagName);
      static void setUpdateCallback(void (*callback)());
      typedef struct {
        std::string id;
        char value;
      } DictionnaryEntry;
    private:
      static void (*cb_)();
      static std::vector<DictionnaryEntry> dictionnary;
      static std::mutex dictionnaryMutex;
  };
}

#endif /* end of include guard: SETTINGS_H */
