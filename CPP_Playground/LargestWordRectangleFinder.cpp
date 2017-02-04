//
//  LargestWordRectangleFinder.cpp
//  CPP_Playground
//
#include "LargestWordRectangleFinder.hpp"
#include <utility>
#include <algorithm>
#include <ctime>

/*
 Word Rectangle:
 Given a list of millions of words, design an algorithm to create the largest possible rectangle of letters
 such that every row forms a word (reading from left to right) and every column forms a word (reading top to bottom).
 THe words need not be chosen consecutively from the list but all rows must be the same length and all columns
 must be the same height.
 */

TrieNode::TrieNode() : stopper(false) {
}

void TrieNode::addWord(const char * word) {
    if (word == nullptr || word[0] == 0) {
        this->stopper = true;
        return;
    }
    char head = word[0];
    const char * tail = word + 1;
    TrieNode* nextNode = NULL;
    if (this->letters.find(head) != this->letters.end()) {
        nextNode = this->letters[head];
    } else {
        nextNode = new TrieNode;
        this->letters.insert(make_pair(head, nextNode));
    }
    if (nextNode) {
        nextNode->addWord(tail);
    }
}

bool TrieNode::hasWord(const char * word) {
    if (word == nullptr || word[0] == 0) {
        return this->stopper;
    }
    char head = word[0];
    const char * tail = word + 1;
    if (this->letters.find(head) != this->letters.end()) {
        return this->letters[head]->hasWord(tail);
    }
    return false;
}

bool TrieNode::hasPrefix(const char * prefix) {
    if (prefix == nullptr || prefix[0] == 0) {
        return true;
    }
    char head = prefix[0];
    const char * tail = prefix + 1;
    if (this->letters.find(head) != this->letters.end()) {
        return this->letters[head]->hasPrefix(tail);
    }
    return false;
}

void getCrossWords(const vector<string>& words, vector<string>& crossWords) {
    crossWords.clear();
    if (!words.empty()) {
        size_t wordLen = words[0].length();
        for (size_t i = 0; i < wordLen; i++) {
            string s = "";
            for (string word : words) {
                s += word[i];
            }
            crossWords.push_back(s);
        }
    }
}

TrieNode * loadTrie(const string& fileName) {
    ifstream input(fileName);
    if (input.fail()) {
        return NULL;
    }
    TrieNode * root = new TrieNode;
    string line;
    while (getline(input, line)) {
        if (!line.empty()) {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            root->addWord(line.c_str());
        }
    }
    input.close();
    return root;
}

void loadWordList(const string& fileName, set<string>& words, size_t maxWordLength = 0) {
    words.clear();
    ifstream input(fileName);
    if (input.fail()) {
        std::cerr << "Could not open file at " << fileName << "\n";
        return;
    }
    string line;
    while (getline(input, line)) {
        if (!line.empty() && (maxWordLength == 0 || line.length() <= maxWordLength)) {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            words.insert(line);
        }
    }
    input.close();
}


void test_loadWordList() {
    set<string> words;
    loadWordList("data/words_small.txt", words);
    for (auto word  : words) {
        cout << word << endl;
    }
}


void test_loadTrie() {
    set<string> words;
    loadWordList("data/words_small.txt", words);
    for (auto word  : words) {
        cout << word << endl;
    }
    TrieNode* root = loadTrie("data/words_small.txt");
    for (auto word  : words) {
        cout << word << ": isPrefix? " << root->hasPrefix(word.c_str()) << " isWord? " << root->hasWord(word.c_str()) << endl;
    }
    for (auto word  : words) {
        word.push_back('x');
        cout << word << ": isPrefix? " << root->hasPrefix(word.c_str()) << " isWord? " << root->hasWord(word.c_str()) << endl;
    }
}

void findLargestRectangle(const set<string>& wordList, vector<vector<string>>& found,
                          int minWidth = 0, int minHeight = 0,
                          const char fileName[] = nullptr, bool ignoreSmaller = false) {
    size_t largestFound = 0;
    map<size_t, TrieNode*> triesByLength;
    map<size_t, vector<string>> wordsByLength;
    size_t maxWordLength = 0;
    ofstream output(fileName != nullptr ? fileName : "/dev/null");
    long counter = 0L;
    time_t timestamp = time(nullptr);
    found.clear();
    for (auto word: wordList) {
        TrieNode * trie;
        if (triesByLength.find(word.length()) != triesByLength.end()) {
            trie = triesByLength[word.length()];
        } else {
            trie = new TrieNode;
            triesByLength.insert(make_pair(word.length(), trie));
        }
        trie->addWord(word.c_str());
        
        wordsByLength[word.length()].push_back(word);
        
        if (maxWordLength < word.length()) {
            maxWordLength = word.length();
        }
    }
    
    for (auto i = maxWordLength; i > minWidth; i--) {
        for (auto j = i; j > minHeight; j--) {
            time_t start = time(nullptr);
            cout << "Searching for rectangles " << i << "x" << j << endl;
            vector<string> words;
            searchRectangles(found, triesByLength, wordsByLength, largestFound, counter, output, ignoreSmaller,
                             timestamp,
                             i, j, words);
            time_t end = time(nullptr);
            cout << "Time spent: " << (end - start) << endl;
        }
    }
    output.close();
}


void searchRectangles(vector<vector<string>>& found, const map<size_t, TrieNode*>& triesByLength,
                      const map<size_t, vector<string>>& wordsByLength,
                      size_t& largestFound,
                      long& counter,
                      ofstream& output,
                      bool ignoreSmaller,
                      time_t timestamp,
                      size_t length, size_t height, vector<string>& words) {
    counter++;

    if (counter % 1000 == 1) {
        time_t now = time(nullptr);
        time_t difference = now - timestamp;
        cout << "Time spent so far: " << difference << endl;
        cout << "Variants checked: " << counter << " (" << (counter / (difference ? difference : 1)) << " per second)" << endl;
    }

    if (ignoreSmaller && (height * length < largestFound)) {
        return;
    }

    if (words.size() > height) {
        return;
    }
    
    if (height - words.size() < 3) {
        cout << "==== Current, tries = " << counter << " ====" << endl;
        for (auto word : words) {
            cout << word << endl;
        }
    }

    if (height == words.size()) {
        if (largestFound < height * length) {
            largestFound = height * length;
        }
        vector<string> result(words.begin(), words.end());
        found.push_back(result);
        cout << "==== Found ====" << endl;
        output << "==== Found ====" << endl;
        for (auto word : words) {
            cout << word << endl;
            output << word << endl;
        }
        return;
    }

    auto trieIter = triesByLength.find(height);
    
    if (trieIter != triesByLength.end()) {
        auto availableWordsIter = wordsByLength.find(length);
        if (availableWordsIter != wordsByLength.end()) {
            set<string> usedWords(words.begin(), words.end());
            for (auto word : availableWordsIter->second) {
                if (usedWords.find(word) == usedWords.end()) {
                    words.push_back(word);
                    
                    vector<string> crossWords;
                    getCrossWords(words, crossWords);
                    bool allGood = true;
                    for (auto crossWord : crossWords) {
                        if (!trieIter->second->hasPrefix(crossWord.c_str())) {
                            allGood = false;
                            break;
                        }
                    }
                        
                    if (allGood) {
                        searchRectangles(found, triesByLength,
                                         wordsByLength,
                                         largestFound,
                                         counter,
                                         output,
                                         ignoreSmaller,
                                         timestamp,
                                         length, height, words);
                    }
                    
                    words.pop_back();
                }
            }
        }
    }
}


const char* DEFAULT_WORD_FILE_LOCATION = "/Users/eyaremenko/dev/CPP_Playground/CPP_Playground/data/words_long.txt";

const unsigned int RECT_SIZE = 7;

const unsigned int MIN_RECT_SIZE = 6;

int main(int argc, char** argv) {
//    test_loadTrie();
    vector<vector<string>> found;
    set<string> wordList;
    const char * fileName = argc >= 2 ? argv[1] : DEFAULT_WORD_FILE_LOCATION;
    std::cout << "Loading word list from " << fileName << "...\n";
    char outputFileName[80];

    sprintf(outputFileName, "rect_%dx%d.txt", RECT_SIZE, RECT_SIZE);

    loadWordList(fileName, wordList, RECT_SIZE);
    std::cout << "Loaded words: " << wordList.size() << "\n";
    findLargestRectangle(wordList, found, MIN_RECT_SIZE, MIN_RECT_SIZE, outputFileName, true);
    return 0;
}
