//
//  chars_all_unique.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/21/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include "chars_all_unique.h"

#include <set>

using namespace std;

bool is_all_unique(const char * str) {
    if (!str) {
        return false;
    }
    set<char> charSet;
    for (const char * p = str; *p; p++) {
        auto it = charSet.find(*p);
        if (it != charSet.end()) {
            return false;
        }
        charSet.insert(*p);
    }
    return true;
}
