//
//  reverse_string.c
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/14/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include <string.h>
#include "reverse_string.h"

char * reverse_string(char * s) {
    if (!s || !strlen(s)) {
        return s;
    }
    char * head = s;
    char * tail = s;
    while (*tail) {
        tail++;
    }
    tail--;
    while (head < tail) {
        char c = *head;
        *head = *tail;
        *tail = c;
        head++;
        tail--;
    }
    return s;
}

