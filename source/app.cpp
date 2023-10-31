#include <app/app.h>
#include <fmt/format.h>

#include <array>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <thread>

using namespace app;

// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.

static void workerThread(WordList &wordList, Word &s_word) {
  bool endEncountered = false;
  while (!endEncountered) {
    if (s_word.data[0])  // Do we have a new word?
    {
      Word *w = new Word(s_word.data);  // Copy the word
      s_word.data[0] = 0;               // Inform the producer that we consumed the word
      endEncountered = std::strcmp(w->data, "end\n") == 0;
      if (!endEncountered) {
        // Do not insert duplicate words
        Word *wordFound = wordList.contains(w->data);
        if (wordFound)
          wordFound->count++;
        else {
          wordList.insertWord(w);
        }
      }
    }
  }
};


void App::run() {
  try {
    // // read input words from stdin (until user enters "end")
    readInputWords();

    // // Print the word list
    std::printf("\n=== Word list:\n");
    wordList.print();

    // start query interface for user to lookup words in list
    lookupWords();

    printf("\n=== Total words found: %d\n", totalWordsFound);
  } catch (std::exception &e) {
    std::printf("error %s\n", e.what());
  }
}

void App::readInputWords() {
  bool endEncountered = false;
  std::thread *worker = new std::thread(&workerThread, std::ref(wordList), std::ref(wordBuffer));
  std::array<char, 32> buffer = {' '};
  wordBuffer.data = new char[32]{' '};
  while (!endEncountered) {
    if (std::fgets(buffer.data(), buffer.size(), stdin)) {
      endEncountered = std::strcoll(buffer.data(), "end\n") == 0;
      // Pass the word to the worker thread
      std::strncpy(wordBuffer.data, buffer.data(), buffer.size());
      while (wordBuffer.data[0])
        ;  // Wait for the worker thread to consume it
    } else if (std::feof(stdin))
      return;
    else if (std::ferror(stdin))
      std::puts("I/O error when reading from stdin.\n");
    else
      std::puts("Unknown stdin error.\n");
  }
  worker->join();  // Wait for the worker to terminate
}

void App::lookupWords() {
  std::array<char, 32> buffer = {' '};

  for (;;) {
    std::printf("\nEnter a word for lookup:\n");

    if (fgets(buffer.data(), buffer.size(), stdin)) {
      // Initialize the word to search for
      Word *w = new Word(buffer.data());
      std::strcpy(w->data, buffer.data());
      // Search for the word
      Word *wordFound = wordList.contains(w->data);
      if (wordFound) {
        std::printf("SUCCESS: '%s' was present %d times in the initial word list\n",
                    Word::delete_char(wordFound->data, '\n'), wordFound->count);
        ++totalWordsFound;
      } else
        std::printf("'%s' was NOT found in the initial word list\n",
                    Word::delete_char(w->data, '\n'));
    } else if (std::feof(stdin))
      return;
    else if (std::ferror(stdin))
      std::puts("I/O error when reading from stdin.");
    else
      std::puts("Unknown stdin error.");
  }
}
