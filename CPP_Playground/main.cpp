//
//  main.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/14/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include <iostream>

extern "C" {
#include "reverse_string.h"
}

#include <utility>

#include "escape_space_chars.h"
#include "chars_all_unique.h"
#include "is_permutation.h"

static char ss[6][20] = {
    "Hello, World!",
    "a ",
    "ab c",
    " a b c d ",
    " "
};

static char uniqueness[4][20] = {
    "",
    "a",
    "abc",
    "abba"
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "sizeof ss: " << sizeof(ss) << '\n';
        std::cout << "sizeof uniqueness: " << sizeof(uniqueness) << '\n';
//    for (int i = 0; i < 5; i++) {
//        char * s = ss[i];
//        std::cout << reverse_string(s) << '\n';
//    }

//    for (int i = 0; i < 5; i++) {
//        char * s = ss[i];
//        std::cout << escape_space_chars(s, 20) << '\n';
//    }
//
//    for (int i = 0; i < 4; i++) {
//        std::cout << uniqueness[i] << (is_all_unique(uniqueness[i]) ? ": all unique\n" : ": not unique\n");
//    }
    

    std::pair<const char *, const char *> anagrams = {"banana", "anaban"};
    std::pair<const char *, const char *> nonAnagrams = {"banana", "aanaba"};
    
    std::cout << "are " << anagrams.first << " and " << anagrams.second << " anagrams? " << is_permutation(anagrams.first, anagrams.second) << '\n';

    std::cout << "are " << nonAnagrams.first << " and " << nonAnagrams.second << " anagrams? " << is_permutation(nonAnagrams.first, nonAnagrams.second) << '\n';

    return 0;
}
