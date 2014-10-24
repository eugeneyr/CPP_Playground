//
//  naive_compression.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/21/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include "naive_compression.h"
#include <utility>
#include <cstring>

// Compresses the string as described in 1.5. MODIFIES THE ARGUMENT!!!
std::pair<CompressionResult, char *> compress_string(char * str) {
    std::pair<CompressionResult, char *> result(OK, str);
    if (!str) {
        return result;
    }
    size_t len = strlen(str);
    char * buffer = new char[len * 10];
    if (!buffer) {
        // memory allocation error
        result.first = ERR_MEMALLOC;
        return result;
    }
    char currChar = 0;
    size_t counter = 0;
    size_t bytesCopied = 0;
    char * currBufPos = buffer;
    for (char * p = str; *p; p++) {
        if (currChar != *p) {
            currChar = *p;
            counter = 0;
        }
        counter++;
        if (*(p + 1) != currChar) {
            // first, check if the length of the resulting string is still less than the length of the original one
            char tmpBuff[32];
            sprintf(tmpBuff, "%zu", counter);
            size_t increment = 1 + strlen(tmpBuff);
            if (bytesCopied + increment >= len) {
                result.first = ERR_NOSPACESAVED;
                delete [] buffer;
                return result;
            }
            
            bytesCopied += increment;
            // flush the accumulated values to the buffer
            *currBufPos++ = currChar;
            strncpy(currBufPos, tmpBuff, 32);
            while (*currBufPos) {
                currBufPos++;
            }
        }
    }
    strncpy(str, buffer, len);
    
    delete [] buffer;
    return result;
}

// Decompresses the string. MODIFIES THE ARGUMENT AND DOES NOT CHECK FOR OVERRUNS!
char * uncompress_sring(char * str) {
    return nullptr;
}
