//
//  is_rotation.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/21/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include "is_rotation.h"

#include <string>

bool is_rotation(const char * s1, const char * s2) {
    if (!s1 || !s2) {
        return false;
    }
    std::string str1(s1);
    std::string str2(s2);
    if (str1.length() != str2.length()) {
        return false;
    }
    std::string conc(s1);
    conc += s1;
    return conc.find(s2) != std::string::npos;
}