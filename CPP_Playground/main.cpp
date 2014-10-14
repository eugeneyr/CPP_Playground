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

int main(int argc, const char * argv[]) {
    // insert code here...
    char * ss[5] = {
        "Hello, World!",
        "a",
        "abc",
        "abcd",
        "Hello, World!"};
    for (int i = 0; i < 5; i++) {
        std::cout << reverse_string(ss[i]) << '\n';
    }
    return 0;
}
