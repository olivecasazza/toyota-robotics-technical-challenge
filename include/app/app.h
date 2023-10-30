#include <app/wordList.h>
#include <string>

namespace app {
  /**
   * @brief A class for saying hello in multiple languages
   */
  class App {
    void readInputWords();
    void lookupWords();
  public:
    WordList wordList;  // memory that stores list of words and frequency
    Word wordBuffer;    // used to pass items between main thread and worker thread
    int totalWordsFound = 0;

    App() {};

    void run();

    void print() { wordList.print(); }
  };

}  // namespace app
