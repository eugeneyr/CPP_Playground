//
//  is_permutation.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/21/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include "is_permutation.h"

#include <utility>
#include <map>
#include <cstring>

extern void build_freq_map(const char * str, std::map<char, int>& freqMap);
extern int count_chars (char c, const char * str);

bool is_permutation(const char * s1, const char * s2) {
    if (!s1) {
        return !s2;
    }
    if (!s2) {
        return !s1;
    }
    if (strlen(s1) != strlen(s2)) {
        return false;
    }
    std::map<char, int> s1FreqMap;
    std::map<char, int> s2FreqMap;
    
    build_freq_map(s1, s1FreqMap);
    build_freq_map(s2, s2FreqMap);
    
    return s1FreqMap == s2FreqMap;
}

void build_freq_map(const char * str, std::map<char, int>& freqMap) {
    if (!str) {
        return;
    }
    for (const char * p = str; *p; p++) {
        int freq = 0;
        auto it = freqMap.find(*p);
        if (it != freqMap.end()) {
            freq = it->second;
        }
        freqMap[*p] = freq + 1;
    }
}

// the version that does not use any additional data structures
bool is_permutation_in_place(const char * s1, const char * s2) {
    if (!s1) {
        return !s2;
    }
    if (!s2) {
        return !s1;
    }
    if (strlen(s1) != strlen(s2)) {
        return false;
    }
    for (const char * p = s1; *p; p++) {
        if (count_chars(*p, s1) != count_chars(*p, s2)) {
            return false;
        }
    }
    return true;
}

int count_chars (char c, const char * str) {
    if (!str) {
        return 0;
    }
    int counter = 0;
    for (const char * p = str; *p; p++) {
        if (*p == c) {
            counter++;
        }
    }
    return counter;
}