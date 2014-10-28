//
//  list.h
//  CPP_Lists
//
//  Created by Svitlana Yaremenko on 10/24/14.
//  Copyright (c) 2014 Eugene Yaremenko. All rights reserved.
//

#ifndef __CPP_Lists__list__
#define __CPP_Lists__list__

#include <iostream>

template <typename T>
class LinkedListNode {
    T data;
    LinkedListNode<T>* next;
    
public:
    LinkedListNode();
    LinkedListNode(const LinkedListNode& otherNode);
    LinkedListNode(const T& someData);
    LinkedListNode& operator=(const LinkedListNode& otherNode);
    virtual ~LinkedListNode();
    void setData(const T& data);
    const T& getData();
    const LinkedListNode<T> * getNext();
    void setNext(const LinkedListNode<T> * next);
};

#endif /* defined(__CPP_Lists__list__) */
