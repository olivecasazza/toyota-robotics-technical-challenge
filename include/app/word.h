#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace app {
  struct Word {
    char *data = new char[32];
    int count = 1;

    Word(char* w) : data(std::move(w)) {};
    Word() : data((char *)""){};
  };

  static inline bool operator<(const Word &lhs, const Word &rhs) {
    return strcmp(lhs.data, rhs.data) < 0;
  }
}