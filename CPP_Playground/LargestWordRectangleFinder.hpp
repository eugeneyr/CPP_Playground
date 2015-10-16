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
    
    void addWord(const string& word);
    
    bool hasWord(const string& word);

    bool hasPrefix(const string& prefix);
};

void getCrossWords(const vector<string>& words, vector<string>& crossWords);

TrieNode * loadTrie(const string& fileName);

#endif /* LargestWordRectangleFinder_hpp */
