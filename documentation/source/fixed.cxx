#include <thread>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

struct Word
{
    char *data = new char[32];
    int count = 1; // human readable count (starts at 1)

    Word(char *data_) : data(::strdup(data_)){};
    Word() : data((char *)""){};
    ~Word()
    {
        if (data)
            delete data;
    };
    Word(Word &source)
    {
        data = new char[strlen(source.data)];
        strcpy(data, source.data);
    };

    void print() {
        printf("Word [data: %s, count: %i]", data, count);
    }

    char * dataStrip() {
        char* tmp = new char[32];
        strcpy(tmp, data);
        *std::remove(tmp, tmp+strlen(tmp), '\n') = '\0';
        return tmp;
    }
};
static std::vector<Word *> s_wordsArray;
static Word s_word;
static int s_totalFound;


static Word* wordListContains(char* data) {
    long unsigned int i = 0;
    while (i < s_wordsArray.size())
    {
        if (std::strcmp(s_wordsArray[i]->data, data) == 0) 
            return s_wordsArray[i];
        i++;
    }
    return NULL;
}

static void printWordList() {
    for (auto word : s_wordsArray) std::printf("%s (%i)\n", word->data, word->count);
}

// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread()
{
    bool endEncountered = false;

    while (!endEncountered)
    {
        if (s_word.data[0]) // Do we have a new word?
        {
            Word *w = new Word(s_word); // Copy the word
            s_word.data[0] = 0; // Inform the producer that we consumed the word
            endEncountered = std::strcmp(w->data, "end\n") == 0;

            if (!endEncountered)
            {
                // Do not insert duplicate words
                Word* wordFound = wordListContains(w->data);
                if(wordFound) wordFound->count++;
                else s_wordsArray.push_back(w);
                printWordList();
            }
        }
    }
};

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords()
{
    bool endEncountered = false;

    std::thread *worker = new std::thread(workerThread);

    std::array<char, 32> buffer;
    s_word.data = new char[32];

    while (!endEncountered)
    {
        if (std::fgets(buffer.data(), buffer.size(), stdin))
        {
            endEncountered = std::strcoll(buffer.data(), "end\n") == 0;
            std::printf("isEndEncountered: %s\n", endEncountered ? "true":"false");
            // Pass the word to the worker thread
            std::strcpy(s_word.data, buffer.data());
            while (s_word.data[0]); // Wait for the worker thread to consume it
        }
        else if (std::feof(stdin)) return;
        else if (std::ferror(stdin)) std::puts("I/O error when reading from stdin.\n");
        else std::puts("Unknown stdin error.\n");
    }
    worker->join(); // Wait for the worker to terminate
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords()
{
    std::array<char, 32> buffer;

    for (;;)
    {
        std::printf("\nEnter a word for lookup:\n");

        if(fgets(buffer.data(), buffer.size(), stdin)) {
            // Initialize the word to search for
            Word *w = new Word(buffer.data());
            std::strcpy(w->data, buffer.data());
            // Search for the word
            Word* wordFound = wordListContains(w->data);
            if (wordFound)
            {
                std::printf(
                    "SUCCESS: '%s' was present %d times in the initial word list\n", 
                    wordFound->dataStrip(),
                    wordFound->count
                );
                ++s_totalFound;
            }
            else std::printf("'%s' was NOT found in the initial word list\n", w->dataStrip());
        }
        else if (std::feof(stdin)) return;
        else if (std::ferror(stdin)) std::puts("I/O error when reading from stdin.");
        else std::puts("Unknown stdin error.");
    }
}

int main()
{
    try
    {
        readInputWords();

        // Sort the words alphabetically
        std::sort(s_wordsArray.begin(), s_wordsArray.end());

        // Print the word list
        std::printf("\n=== Word list:\n");
        printWordList();
        lookupWords();

        printf("\n=== Total words found: %d\n", s_totalFound);
    }
    catch (std::exception &e)
    {
        std::printf("error %s\n", e.what());
    }

    return 0;
}