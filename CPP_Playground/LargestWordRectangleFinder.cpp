//
//  LargestWordRectangleFinder.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/15/15.
//  Copyright © 2015 Yevhen Yaremenko. All rights reserved.
//

#include "LargestWordRectangleFinder.hpp"
#include <utility>
#include <algorithm>

/*
 Word Rectangle:
 Given a list of millions of words, design an algorithm to create the largest possible rectangle of letters
 such that every row forms a word (reading from left to right) and every column forms a word (reading top to bottom).
 THe words need not be chosen consecutively from the list but all rows must be the same length and all columns
 must be the same height.
 */

TrieNode::TrieNode() : stopper(false) {
}

void TrieNode::addWord(const string& word) {
    if (word.empty()) {
        this->stopper = true;
        return;
    }
    char head = word[0];
    string tail = word.substr(1);
    TrieNode* nextNode = NULL;
    if (this->letters.find(head) != this->letters.end()) {
        nextNode = this->letters[head];
    } else {
        nextNode = new TrieNode;
        pair<char, TrieNode*> p(head, nextNode);
        this->letters.insert(p);
    }
    if (nextNode) {
        nextNode->addWord(tail);
    }
}

bool TrieNode::hasWord(const string &word) {
    if (word.empty()) {
        return this->stopper;
    }
    char head = word[0];
    string tail = word.substr(1);
    if (this->letters.find(head) != this->letters.end()) {
        return this->letters[head]->hasWord(tail);
    }
    return false;
}

bool TrieNode::hasPrefix(const string &prefix) {
    if (prefix.empty()) {
        return true;
    }
    char head = prefix[0];
    string tail = prefix.substr(1);
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
            root->addWord(line);
        }
    }
    input.close();
    return root;
}

void loadWordList(const string& fileName, set<string>& words, size_t maxWordLength = 0) {
    words.clear();
    ifstream input(fileName);
    if (input.fail()) {
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

/*
namespace {
    auto listPrinter = [] (int x) {std::cout << x << std::endl;};
}
*/

void test_loadWordList() {
    set<string> words;
    loadWordList("data/words_small.txt", words);
    for (auto word  : words) {
        cout << word << endl;
    }
}

int main(int argc, char** argv) {
    test_loadWordList();
}


/*
 import copy
 import time
 
 
def findLargestRectangle(wordList, minWidth=0, minHeight=0, outputFileName=None, ignoreSmaller=False):
    largestFound = 0
    bigTrie = TrieNode()
    triesByLength = {}
    wordsByLength = {}
    maxWordLength = 0
    found = []
    output = None
    counter = 0
    timestamp = time.time()

    def searchRectangles(length, height, words):
        nonlocal largestFound
        nonlocal counter

        counter += 1

        if counter % 1000 == 1:
            now = time.time()
            difference = now - timestamp
            print('Time spent so far: {:.3f}s'.format(difference))
            print('Variants checked: {} ({:.3f} per second(counter)'.format(counter, (counter + 1) / difference))
        if ignoreSmaller and (height * length < largestFound):
            return
        # Stops the recursion: the rectangle cannot be larger than that
        if len(words) > height:
            return

        if height - len(words) < 3:
            print('==== Current, tries = {} ===='.format(counter))
            for word in words:
                print(word)
        # If the number of the words == height, it is a valid rectangle. Store it and exit.
        if len(words) == height:
            if largestFound < height * length:
                largestFound = height * length
            found.append(copy.deepcopy(words))
            print('==== Found ====', file=output, flush=True)
            for word in words:
                print(word, file=output, flush=True)
            if output is not None:
                print('==== Found ====')
                for word in words:
                    print(word)
            return

        trie = triesByLength.get(height)
        if trie is not None:
            usedWords = set(words)
            availableWords = wordsByLength.get(length)
            if availableWords is not None:
                for word in availableWords:
                    if word not in usedWords:
                        # check if cross words of words + word are prefixes of existing words
                        words.append(word)
                        crossWords = getCrossWords(words)
                        allGood = True
                        for crossWord in crossWords:
                            if not trie.hasPrefix(crossWord):
                                allGood = False
                                break
                        if allGood:
                            # go one level deeper
                            searchRectangles(length, height, words)
                        words.pop()

    if outputFileName is not None:
        output = open(outputFileName, 'w')

    try:
        for word in wordList:
            bigTrie.addWord(word)
            trie = triesByLength.get(len(word), TrieNode())
            trie.addWord(word)
            triesByLength[len(word)] = trie
            words = wordsByLength.get(len(word), set())
            words.add(word)
            wordsByLength[len(word)] = words
            if len(word) > maxWordLength:
                maxWordLength = len(word)
        for i in range(maxWordLength, minWidth, -1):
            for j in range(i, minHeight, -1):
                start = time.time()
                print('Searching for rectangles {} x {}'.format(i, j))
                searchRectangles(i, j, [])
                end = time.time()
                print('Time spent: {:.3f} s'.format(end - start))
    finally:
        if output is not None:
            output.close()

    return found



import unittest


class FindRectangleTest(unittest.TestCase):
    @unittest.skip
    def test_smallList(self):
        found = findLargestRectangle(['sator', 'arepo', 'tenet', 'opera', 'rotas'])
        for words in found:
            print('==== Found ====')
            for word in words:
                print(word)

    @unittest.skip
    def test_mediumlList(self):
        found = findLargestRectangle(loadWordList('../../data/words.txt', maxWordLength=5), minWidth=4, minHeight=4,
                                     ignoreSmaller=True)
        for words in found:
            print('==== Found ====')
            for word in words:
                print(word)

    def test_mediumlList_save7(self):
        found = findLargestRectangle(loadWordList('../../data/words.txt', maxWordLength=7), minWidth=6, minHeight=6,
                                     ignoreSmaller=True, outputFileName='../../data/rect_7x7.txt')
        self.assertTrue(len(found) > 0)

    @unittest.skip
    def test_mediumlList_save(self):
        found = findLargestRectangle(loadWordList('../../data/words.txt', maxWordLength=6), minWidth=5, minHeight=5,
                                     ignoreSmaller=True, outputFileName='../../data/rect_6x6.txt')
        self.assertTrue(len(found) > 0)

    @unittest.skip
    def test_biglList(self):
        found = findLargestRectangle(loadWordList('../../data/words.txt', maxWordLength=6), minWidth=5, minHeight=5)
        for words in found:
            print('==== Found ====')
            for word in words:
                print(word)


if __name__ == '__main__':
    unittest.main()
 
 
 */