#include <app/word.h>

#include <algorithm>
#include <cstring>
#include <set>
#include <string>

namespace app {

  struct cstrless {
    bool operator()(Word *a, Word *b) const { return strcmp(a->data, b->data) < 0; }
  };

  class WordList {
  public:
    std::set<Word *, cstrless> s_wordsArray;
    Word *contains(char *data) {
      for (auto w = s_wordsArray.begin(); w != s_wordsArray.end(); w++)
        if (strcmp((*w)->data, data) == 0) return *w;
      return nullptr;
    }

    void print() {
      for (auto w = s_wordsArray.begin(); w != s_wordsArray.end(); w++)
        std::cout << (*w)->data << " #: " << (*w)->count << std::endl;
    }

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
