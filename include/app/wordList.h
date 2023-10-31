#include <app/word.h>

#include <algorithm>
#include <cstring>
#include <set>
#include <string>

namespace app {

  struct cstrless {
    bool operator()(Word *a, Word *b) const { return strcmp(a->data, b->data) < 0; }
  };

  /// @brief a data structure used to store a list of words in order.
  class WordList {
  public:
    std::set<Word *, cstrless> s_wordsArray;

    /// @brief check to see if a word (char* ) has been entered into the word list.
    /// @param data the word (char* ) to check the word list for.
    /// @return if the word has been previously entered, return the word.
    Word *contains(char *data) {
      for (auto w = s_wordsArray.begin(); w != s_wordsArray.end(); w++)
        if (strcmp((*w)->data, data) == 0) return *w;
      return nullptr;
    }

    /// @brief print the word list to stdout in order
    void print() {
      for (auto w = s_wordsArray.begin(); w != s_wordsArray.end(); w++)
        std::cout << (*w)->data << " #: " << (*w)->count << std::endl;
    }

    /// @brief insert a new word into the list, if it has already been entered, increase the count
    /// of the word.
    /// @param word the word to insert into the list.
    /// @return the word inserted into (or already existed in) into the list
    Word *insertWord(Word *word) {
      for (auto w = s_wordsArray.begin(); w != s_wordsArray.end(); w++)
        if (strcmp((*w)->data, word->data) == 0) {
          (*w)->count++;
          return (*w);
        }
      s_wordsArray.insert(word);
      return word;
    }
  };
}  // namespace app
