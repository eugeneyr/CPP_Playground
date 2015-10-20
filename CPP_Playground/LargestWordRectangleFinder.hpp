//
//  LargestWordRectangleFinder.hpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/15/15.
//  Copyright © 2015 Yevhen Yaremenko. All rights reserved.
//

#ifndef LargestWordRectangleFinder_hpp
#define LargestWordRectangleFinder_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

struct TrieNode {
    bool stopper;

    map<char, TrieNode*> letters;
    
    TrieNode();
    
    void addWord(const char * word);
    
    bool hasWord(const char * word);

    bool hasPrefix(const char * prefix);
};

void getCrossWords(const vector<string>& words, vector<string>& crossWords);

TrieNode * loadTrie(const string& fileName);

void searchRectangles(vector<vector<string>>& found, const map<size_t, TrieNode*>& triesByLength,
                      const map<size_t, vector<string>>& wordsByLength,
                      size_t& largestFound,
                      long& counter,
                      ofstream& output,
                      bool ignoreSmaller,
                      time_t timestamp,
                      size_t length, size_t height, vector<string>& words);

#endif /* LargestWordRectangleFinder_hpp */
