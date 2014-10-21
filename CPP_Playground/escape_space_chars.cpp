#include "escape_space_chars.h"
#include <string>

char * escape_space_chars(char * string, size_t capacity) {
    if (!string) {
        return string;
    }
    size_t len = strlen(string);
    if (!len) {
        return string;
    }
    size_t noOfSpaces = 0;
    char * p = NULL;
    for (p = string; *p; p++) {
        if (*p == ' ') {
            noOfSpaces++;
        }
    }
    if (noOfSpaces * 2 + len > capacity) {
        // TODO should handle the error here - the chunk of memory allocated for the string is not large enough
        return string;
    }
    char * tail = string + len + noOfSpaces * 2;
    while (p >= string) {
        if (*p != ' ') {
            *tail-- = *p--;
        } else {
            if (p > string) {
                p--;
            }
            *tail-- = '0';
            *tail-- = '2';
            *tail-- = '%';
        }
    }
    
    return string;
}
