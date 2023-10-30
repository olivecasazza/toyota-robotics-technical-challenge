#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace app {
  struct Word {
    char *data = new char[32];
    int count = 1;

    Word(char *data_) : data(::strdup(data_)){};
    Word() : data((char *)""){};
  };
}