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
#include <exception>
#include <stdexcept>
#include <stack>
#include <vector>

// 3.1. Describe how you could use a single array to implement three stacks.
// TODO: there could be situations when teh stack A is filled up while there is still some space on the top of the stack B.
// Implement "overflowing" of data from one stack to unused space in another.
template <typename T>
class Stack {
public:
    virtual T pop() = 0;
    virtual void push(T& elem) = 0;
    virtual T& peek() = 0;
};

const int NUMBER_OF_STACKS = 3;

template <typename T, size_t size>
class ThreeStackArray {
private:
    T ** data;
    size_t tops[NUMBER_OF_STACKS];
public:
    ThreeStackArray() {
        data = new T*[size * NUMBER_OF_STACKS];
        for (int i = 0; i < size * NUMBER_OF_STACKS; i++) {
            data[i] = nullptr;
        }
        for (int i = 0; i < NUMBER_OF_STACKS; i++) {
            tops[i] = 0;
        }
    }
    
    virtual ~ThreeStackArray() {
        if (data != nullptr) {
            delete [] data;
        }
    }
    
    T * pop(size_t stackIdx);
    T * peek(size_t stackIdx);
    void push(size_t stackIdx, T * element);
    size_t getSize(size_t stackIdx);
};

template <typename T, size_t size> T * ThreeStackArray<T, size>::pop(size_t stackIdx) {
    if (stackIdx >= NUMBER_OF_STACKS) {
        throw std::logic_error("Invalid stack index");
    }
    if (tops[stackIdx] == 0) {
        throw std::logic_error("Empty stack");
    }
    T * ret = data[stackIdx + (tops[stackIdx] - 1) * NUMBER_OF_STACKS];
    data[stackIdx + (tops[stackIdx] - 1) * NUMBER_OF_STACKS] = nullptr;
    tops[stackIdx]--;
    return ret;
}

template <typename T, size_t size> T * ThreeStackArray<T, size>::peek(size_t stackIdx) {
    if (stackIdx >= NUMBER_OF_STACKS) {
        throw std::logic_error("Invalid stack index");
    }
    if (tops[stackIdx] == 0) {
        throw std::logic_error("Empty stack");
    }
    T * ret = data[stackIdx + (tops[stackIdx] - 1) * NUMBER_OF_STACKS];
    return ret;
}

template <typename T, size_t size> void ThreeStackArray<T, size>::push(size_t stackIdx, T * element) {
    if (stackIdx >= NUMBER_OF_STACKS) {
        throw std::logic_error("Invalid stack index");
    }
    if (tops[stackIdx] == size) {
        throw std::logic_error("Stack is full");
    }
    data[(stackIdx + tops[stackIdx] * NUMBER_OF_STACKS)] = element;
    tops[stackIdx]++;
}

template <typename T, size_t size> size_t ThreeStackArray<T, size>::getSize(size_t stackIdx) {
    if (stackIdx >= NUMBER_OF_STACKS) {
        throw std::logic_error("Invalid stack index");
    }
    return tops[stackIdx];
}

// How would you design a stack which, in addition to push and pop, also has a function min which returns the minimum element?
// Push, pop and min should all operate in O(1) time.
template <typename T>
class MinHoldingStack {
    std::stack<T> wrapped;
    std::stack<T> minStack;
public:
    MinHoldingStack() {
    }
    
    T& top() {
        return wrapped.top();
    }
    
    T& min() {
        return minStack.top();
    }
    
    const T& top() const {
        return wrapped.top();
    }
    
    bool empty() const {
        return wrapped.empty();
    }
    
    size_t size() const {
        return wrapped.size();
    }
    
    void push(const T& value) {
        wrapped.push(value);
        if (minStack.empty() || minStack.top() >= value) {
            minStack.push(value);
        }
    }
    
    void push(T&& value) {
        wrapped.push(value);
        if (minStack.empty() || minStack.top() >= value) {
            minStack.push(value);
        }
    }
    
    void pop() {
        if (!wrapped.empty()) {
            T& top = wrapped.top();
            if (top == minStack.top()) {
                minStack.pop();
            }
            wrapped.pop();
        }
    }    
};

template <typename T, size_t stackSize>
class SetOfStacks {
    std::vector<std::vector<T>> vectorOfStacks;
    size_t currentSize;
public:
    SetOfStacks() : currentSize(0) {
    }
    
    T& peek();
    void push(T& element);
    T pop();
    size_t size();
    bool empty();
    size_t noOfStacks();
    T popAt(size_t stackIdx);
};

template <typename T, size_t stackSize> void SetOfStacks<T, stackSize>::push(T& element) {
    if (vectorOfStacks.empty()) {
        std::vector<T> newStack;
        newStack.push_back(element);
        vectorOfStacks.push_back(newStack);
    } else {
        std::vector<T>& currentStack = vectorOfStacks[vectorOfStacks.size() - 1];
        size_t currSize = currentStack.size();
        if (currSize >= stackSize) {
            std::vector<T> newStack;
            newStack.push_back(element);
            vectorOfStacks.push_back(newStack);
        } else {
            currentStack.push_back(element);
        }
    }
    currentSize++;
}

template <typename T, size_t stackSize> T SetOfStacks<T, stackSize>::pop() {
    if (currentSize == 0) {
        throw std::underflow_error("Empty stack");
    }
    while (!vectorOfStacks.empty() && vectorOfStacks.back().empty()) {
        vectorOfStacks.pop_back();
    }
    if (vectorOfStacks.empty()) {
        throw std::underflow_error("Empty stack");
    }
    std::vector<T>& currStack = vectorOfStacks.back();
    T& val = currStack.back();
    
    currStack.pop_back();
    if (currStack.empty()) {
        vectorOfStacks.pop_back();
    }
    currentSize--;
    return val;
}

template <typename T, size_t stackSize> size_t SetOfStacks<T, stackSize>::size() {
    return currentSize;
}

template <typename T, size_t stackSize> bool SetOfStacks<T, stackSize>::empty() {
    return currentSize == 0;
}

template <typename T, size_t stackSize> size_t SetOfStacks<T, stackSize>::noOfStacks() {
    return vectorOfStacks.size();
}

template <typename T, size_t stackSize> T SetOfStacks<T, stackSize>::popAt(size_t stackIdx) {
    if (currentSize == 0) {
        throw std::underflow_error("Empty stack");
    }
    if (vectorOfStacks.size() <= stackIdx) {
        throw std::logic_error("this SetOfStacks does not have a stack with requested idx");
    }
    std::vector<T>& stack = vectorOfStacks[stackIdx];
    if (stack.empty()) {
        throw std::underflow_error("Stack with requested idx is empty");
    }
    T& val = stack.back();
    stack.pop_back();
    if (stack.empty()) {
        vectorOfStacks.erase(vectorOfStacks.cbegin() + stackIdx);
    }
    currentSize--;
    return val;
}

void test_three_stacks();


#endif /* defined(__CPP_Playground__chapter3__) */
