#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

namespace app {

  /// @brief a data structure used to store words (char* ) and a integer to count the frequency that the word was entered.
  struct Word {
    char *data = new char[32];
    int count = 1;

    Word(char *data_) : data(::strdup(data_)) {}
    Word() : data((char *)""){};

    /// @brief check if a word contains only alphanumeric characters.
    /// @param buf the char* to check for invalid characters
    /// @return boolean indicating if the word only contains alphanumeric characters.
    static bool isValid(char *buf) {
      size_t buflen = strlen(buf);
      for (size_t i = 0; i < buflen; ++i)
        if (isalnum(buf[i]) || buf[i] != ' ') return false;
      return true;
    }

    /// @brief helper function used to remove specific characters from char*
    /// @param sourceArray the char* that 
    /// @param inputChar the character to remove
    /// @return the pointer to the updated character array
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
  };
}  // namespace app