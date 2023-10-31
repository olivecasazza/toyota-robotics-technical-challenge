#include <app/wordList.h>

#include <string>

namespace app {
  /**
   * @brief A class for storing a user's inputs words and their frequency, then providing a query
   * interface to search the list of words entered.
   */
  class App {
    /// @brief Read input words from STDIN and pass them to the worker thread for inclusion in the
    /// word list. Terminate when the word 'end' has been entered.
    void readInputWords();

    /// @brief Repeatedly ask the user for a word and check whether it was present in the word list.
    /// Terminate on EOF.
    void lookupWords();

  public:
    WordList wordList;  // memory that stores list of words and frequency
    Word wordBuffer;    // used to pass items between main thread and worker thread
    int totalWordsFound = 0;

    /// @brief Create a new program instance
    App(){};

    /// @brief Run the program
    void run();

    /// @brief Print the current word list stored in the program to stdout
    void print() { wordList.print(); }
  };

}  // namespace app
