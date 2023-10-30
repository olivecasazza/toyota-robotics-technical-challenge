#include <app/app.h>
#include <app/version.h>
#include <doctest/doctest.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace app;

TEST_CASE("Word list inserts and counts duplicate words correctly.") {
  WordList wordList = WordList();
  
  std::vector<Word* > words = {
    new Word((char *)"bar"),
    new Word((char *)"baz"),
    new Word((char *)"foo"),
    new Word((char *)"foo"),
    new Word((char *)"foo"),
    new Word((char *)"foo")
  };

  for (auto i : words) wordList.insertWord(i);

  CHECK_EQ(wordList.s_wordsArray.size(), 3);

  Word* foo = wordList.contains((char *)"foo");
  CHECK_EQ(foo->data, (char*)"foo");
  CHECK_EQ(foo->count, 4);

  Word* bar = wordList.contains((char *)"bar");
  CHECK_EQ(bar->data, (char*)"bar");
  CHECK_EQ(bar->count, 1);


  Word* baz = wordList.contains((char *)"baz");
  CHECK_EQ(baz->data, (char*)"baz");
  CHECK_EQ(baz->count, 1);
}


TEST_CASE("Word list sorts items when printed.") {
  WordList wordList = WordList();
  wordList.insertWord(new Word((char *)"foo"));
  wordList.insertWord(new Word((char *)"baz"));
  wordList.insertWord(new Word((char *)"bar"));
  
  std::vector <Word* > output;
  std::vector <Word* > expected = {
    new Word((char *)"bar"),
    new Word((char *)"baz"),
    new Word((char *)"foo")
  };

  for (auto i : expected) {
    output.push_back(i);
  }

  for(int i = 0; i < 3; i++){
    CHECK_EQ(output[i]->data, expected[i]->data);
    CHECK_EQ(output[i]->count, expected[i]->count);
  }
}