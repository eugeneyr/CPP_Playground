//
//  chapter3.h
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/31/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#ifndef __CPP_Playground__chapter3__
#define __CPP_Playground__chapter3__

#include <stdio.h>

template <typename T>
class Stack {
public:
    T pop() = 0;
    void push(T& elem) = 0;
    T& peek() = 0;
};

#endif /* defined(__CPP_Playground__chapter3__) */
