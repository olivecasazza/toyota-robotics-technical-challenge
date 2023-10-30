#include <app/wordList.h>
#include <string>

namespace app {
  /**
   * @brief A class for saying hello in multiple languages
   */
  class App {
    
  public:
    WordList wordList;  // memory that stores list of words and frequency
    Word wordBuffer;    // used to pass items between main thread and worker thread
    int totalWordsFound = 0;

    /**
     * @brief Creates a new app
     */
    App();

    void readInputWords();
    void lookupWords();
    void run();
    void print();
  };

}  // namespace app
