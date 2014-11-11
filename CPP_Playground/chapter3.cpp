//
//  chapter3.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/31/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//
#include <iostream>
#include <vector>
#include "chapter3.h"

void test_three_stacks() {
    ThreeStackArray<int, 10> stack;
    for (int i = 0; i < 30; i++) {
        stack.push(i % 3, new int(i));
    }
    for (int i = 0; i < 3; i++) {
        std::cout << "Stack #" << i << ":" << std::endl;
        while (stack.getSize(i) > 0) {
            int * pval = stack.pop(i);
            std::cout << (pval ? *pval : -1) << std::endl;
            delete pval;
        }
    }
}

void test_min_stack() {
    MinHoldingStack<int> stacko;
    std::vector<int> v({4, 4, 2, 4, 2, 3, 3, 5, 1, 0, 1, 2, 0, 0});
    for (auto x : v) {
        stacko.push(x);
        std::cout << "Pushed: " << x << " Min: " << stacko.min() << std::endl;
    }
    while (!stacko.empty()) {
        int x = stacko.top();
        int min  = stacko.min();
        stacko.pop();
        std::cout << "Popped: " << x << " Min: " << min << std::endl;
        if (!stacko.empty()) {
            std::cout << "Current min: " << stacko.min() << std::endl;
        }
    }
}

void test_set_of_stacks() {
    SetOfStacks<int, 2> sos;
    for (int i = 0; i < 10; i++) {
        sos.push(i);
    }
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    std::cout << "Popping stuff:\n";
    while (!sos.empty()) {
        std::cout << sos.pop() << std::endl;
    }
    std::cout << "Number of stacks afterwards: " << sos.noOfStacks() << std::endl;
}

void test_set_of_stacks_popAt() {
    SetOfStacks<int, 2> sos;
    for (int i = 0; i < 10; i++) {
        sos.push(i);
    }
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    
    std::cout << "Popping from the middle:\n";
    std::cout << sos.popAt(2) << std::endl;
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    std::cout << sos.popAt(2) << std::endl;
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    std::cout << sos.popAt(3) << std::endl;
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    std::cout << sos.popAt(3) << std::endl;
    std::cout << "Number of stacks: " << sos.noOfStacks() << std::endl;
    
    std::cout << "Popping the rest:\n";
    while (!sos.empty()) {
        std::cout << sos.pop() << std::endl;
    }
    std::cout << "Number of stacks afterwards: " << sos.noOfStacks() << std::endl;
}

// 3.4. In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of different
// sizes which can slide onto any tower. The puzzle starts with disks sorted in ascending order
// of size from top to bottom
// (i.e., each disk sits on top of an even larger one).
// You have the following constraints:
// (1) Only one disk can be moved at a time.
// (2) A disk is slid off the top of one tower onto the next tower.
// (3) A disk can only be placed on top of a larger disk.
// Write a program to move the disksfrom the first tower to the last using stacks.

typedef std::pair<std::string, std::stack<int>> Tower;

bool can_slide(int disk, Tower& tower) {
    return tower.second.empty() || tower.second.top() > disk;
}

bool slide(Tower& towerA, Tower& towerB) {
    if (towerA.second.empty()) {
        return true;
    }
    int top = towerA.second.top();
    if (can_slide(top, towerB)) {
        std::cout << towerA.first << " to " << towerB.first << ": " << towerA.second.top() << std::endl;
        towerA.second.pop();
        towerB.second.push(top);
        return true;
    }
    return false;
}

typedef std::pair<std::string, std::stack<int>> Tower;

void towers_of_hanoi(Tower& towerA, Tower& towerB, Tower& towerC, unsigned long n) {
    switch (n) {
        case 0:
            return;
        case 1:
            slide(towerA, towerC);
            return;
        default:
            towers_of_hanoi(towerA, towerC, towerB, n - 1);
            slide(towerA, towerC);
            towers_of_hanoi(towerB, towerA, towerC, n - 1);
    }
}

void towers_of_hanoi(Tower& towerA, Tower& towerB, Tower& towerC) {
    towers_of_hanoi(towerA, towerB, towerC, towerA.second.size());
}

void pop_all(Tower& tower) {
    std::cout << "All of tower " << tower.first << std::endl;
    while (!tower.second.empty()) {
        int i = tower.second.top();
        std::cout << i << std::endl;
        tower.second.pop();
    }
}

void test_towers_of_hanoi() {
    int no_of_disks = 8;
    Tower towerA(std::string("A"), std::stack<int>());
    for (int i = no_of_disks; i > 0; i--) {
        towerA.second.push(i);
    }
    Tower towerB(std::string("B"), std::stack<int>());
    Tower towerC(std::string("C"), std::stack<int>());
    towers_of_hanoi(towerA, towerB, towerC);
    pop_all(towerA);
    pop_all(towerB);
    pop_all(towerC);
}


int main(int argc, char ** argv) {
    //test_three_stacks();
    //test_min_stack();
    //test_set_of_stacks();
    // test_set_of_stacks_popAt();
    test_towers_of_hanoi();
    return 0;
}