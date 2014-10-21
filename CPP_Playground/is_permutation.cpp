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

