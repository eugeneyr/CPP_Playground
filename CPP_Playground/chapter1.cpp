//
//  main.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/14/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include <iostream>

//extern "C" {
#include "reverse_string.h"
//}

#include <utility>

#include "chapter1.h"

//static char ss[6][32] = {
//    "Hello, World!",
//    "a ",
//    "ab c",
//    " a b c d ",
//    " "
//};
//
//static char uniqueness[4][20] = {
//    "",
//    "a",
//    "abc",
//    "abba"
//};


int chapter1_tests(int argc, const char * argv[]) {
//    std::cout << "sizeof ss: " << sizeof(ss) << '\n';
//    std::cout << "sizeof uniqueness: " << sizeof(uniqueness) << '\n';
    //    for (auto s : ss) {
    //        std::cout << reverse_string(s) << '\n';
    //    }
    //
    //    for (auto s : ss) {
    //        std::cout << escape_space_chars(s, 20) << '\n';
    //    }
    //
    //    for (int i = 0; i < 4; i++) {
    //        std::cout << uniqueness[i] << (is_all_unique(uniqueness[i]) ? ": all unique\n" : ": not unique\n");
    //    }
    
    //    {
    //        std::pair<const char *, const char *> anagrams = {"banana", "anaban"};
    //        std::pair<const char *, const char *> nonAnagrams = {"banana", "aanaba"};
    //
    //        std::cout << "are " << anagrams.first << " and " << anagrams.second << " anagrams? " << is_permutation(anagrams.first, anagrams.second) << '\n';
    //
    //        std::cout << "are " << nonAnagrams.first << " and " << nonAnagrams.second << " anagrams? " << is_permutation(nonAnagrams.first, nonAnagrams.second) << '\n';
    //
    //        std::cout << "are " << anagrams.first << " and " << anagrams.second << " anagrams? " << is_permutation_in_place(anagrams.first, anagrams.second) << '\n';
    //
    //        std::cout << "are " << nonAnagrams.first << " and " << nonAnagrams.second << " anagrams? " << is_permutation_in_place(nonAnagrams.first, nonAnagrams.second) << '\n';
    //    }
    {    std::pair<const char *, const char *> rotations = {"abc", "cab"};
        std::pair<const char *, const char *> nonRotations = {"abdadad", "dadadba"};
        
        std::cout << "is " << rotations.first << " a rotation of " << rotations.second << "? " << is_rotation(rotations.first, rotations.second) << '\n';
        
        std::cout << "is " << nonRotations.first << " a rotation of " << nonRotations.second << "? " << is_rotation(nonRotations.first, nonRotations.second) << '\n';
    }
    {
        char s[20] = "aaabbcddddde";
        std::pair<CompressionResult, char *> compRes = compress_string(s);
        std::cout << "Err code: " << compRes.first << '\n' << "Compression result: " << compRes.second << '\n';
    }
    //        {
    //            char s[20] = "a";
    //            std::pair<CompressionResult, char *> compRes = compress_string(s);
    //            std::cout << "Err code: " << compRes.first << '\n' << "Compression result: " << compRes.second << '\n';
    //        }
    //        {
    //            char s[20] = "abcd";
    //            std::pair<CompressionResult, char *> compRes = compress_string(s);
    //            std::cout << "Err code: " << compRes.first << '\n' << "Compression result: " << compRes.second << '\n';
    //        }
    {
        char s[20] = "aaa";
        std::pair<CompressionResult, char *> compRes = compress_string(s);
        std::cout << "Err code: " << compRes.first << '\n' << "Compression result: " << compRes.second << '\n';
    }
    
    {
        SquareMatrix m(6);
        for (int x = 0; x < m.getSize(); x++) {
            for (int y = 0; y < m.getSize(); y++) {
                m.setCell(x, y, 0);
            }
        }
        m.setCell(2, 1, 1);
        m.setCell(3, 1, 1);
        m.setCell(1, 3, 1);
        m.setCell(4, 3, 1);
        m.setCell(2, 4, 1);
        m.setCell(3, 4, 1);
        std::cout << '\n';
        m.print();
        m.rotate_90_degrees();
        std::cout << '\n';
        m.print();
        m.rotate_90_degrees();
        std::cout << '\n';
        m.print();
        m.rotate_90_degrees();
        std::cout << '\n';
        m.print();
        m.rotate_90_degrees();
        std::cout << '\n';
        m.print();
    }
    
    {
        Matrix m(5, 4);
        for (int i = 0; i < m.getSizeX(); i++) {
            for (int j = 0; j < m.getSizeY(); j++) {
                m.setCell(i, j, 1 + i * j);
            }
        }
        m.print();
        m.setCell(1, 0, 0.0);
        m.setCell(3, 2, 0.0);
        m.zeroify();
        std::cout << std::endl;
        m.print();
    }
    
    return 0;
}
