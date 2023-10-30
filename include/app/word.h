#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace app {
  struct Word {
    char *data = new char[32];
    int count = 1;

    Word(char *data_) : data(::strdup(data_)) {}
    Word() : data((char *)""){};

    static bool isValid(char * buf) {
      size_t buflen = strlen(buf);
      for (size_t i = 0; i < buflen; ++i) 
        if (isalnum(buf[i]) || buf[i] != ' ') return false;
      return true;
    }

    static char *delete_char(char *sourceArray, char inputChar) {
      int iNr = 0, iSize, j = 0;

      iSize = strlen(sourceArray);

      for (int i = 0; i < iSize; i++)
        if (sourceArray[i] == inputChar) iNr++;

      char *newarray = new char[iNr + 1];

      for (int i = 0; i < iSize; i++) {
        if (sourceArray[i] != inputChar) newarray[j++] = sourceArray[i];
      }

      return newarray;
    }
    static int sizeofArray(char *sourceArray) { return strlen(sourceArray); }
  };
}  // namespace app