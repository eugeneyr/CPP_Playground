//
//  naive_compression.h
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/21/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#ifndef __CPP_Playground__naive_compression__
#define __CPP_Playground__naive_compression__

#include <stdio.h>
#include <utility>

typedef enum { OK = 0, ERR_NOSPACESAVED, ERR_MEMALLOC } CompressionResult;

// Compresses the string as described in 1.5. MODIFIES THE ARGUMENT!!!
extern std::pair<CompressionResult, char *> compress_string(char * str);

// Decompresses the string. MODIFIES THE ARGUMENT AND DOES NOT CHECK FOR OVERRUNS!
extern char * uncompress_sring(char * str);

#endif /* defined(__CPP_Playground__naive_compression__) */
