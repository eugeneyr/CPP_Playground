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
    LinkedListNode(const LinkedListNode<T>& otherNode);
    LinkedListNode(const T& someData);
    LinkedListNode(T& someData);
    LinkedListNode& operator=(const LinkedListNode<T>& otherNode);
    LinkedListNode(LinkedListNode<T>&& someData);
    LinkedListNode& operator=(LinkedListNode<T>&& otherNode);
    virtual ~LinkedListNode();
    void setData(T& data);
    T& getData();
    const T& getData() const;
    LinkedListNode<T> * getNext();
    const LinkedListNode<T> * getNext() const;
    void setNext(LinkedListNode<T> * next);
};

template <typename T> LinkedListNode<T>::LinkedListNode() : next(nullptr) {
}

template <typename T> LinkedListNode<T>::LinkedListNode(const LinkedListNode<T>& other) : next(other.next), data(other.data) {
}

template <typename T> LinkedListNode<T>::LinkedListNode(const T& someData) : data(someData), next(nullptr) {
}

template <typename T> LinkedListNode<T>::LinkedListNode(T& someData) : data(someData), next(nullptr) {
}

template <typename T> LinkedListNode<T>::~LinkedListNode() {
}

template <typename T> T& LinkedListNode<T>::getData() {
    return data;
}

template <typename T> const T& LinkedListNode<T>::getData() const {
    return data;
}

template <typename T> void LinkedListNode<T>::setData(T &data) {
    this->data = data;
}

template <typename T> LinkedListNode<T>* LinkedListNode<T>::getNext() {
    return this->next;
}

template <typename T> const LinkedListNode<T>* LinkedListNode<T>::getNext() const {
    return this->next;
}

template <typename T> void LinkedListNode<T>::setNext(LinkedListNode<T> * next) {
    this->next = next;
}

template <typename T> LinkedListNode<T>& LinkedListNode<T>::operator = (const LinkedListNode<T>& other) {
    if (this != &other) {
        this->next = other.getNext();
        this->data = other.getData();
    }
    return *this;
}

// Move ctor
template <typename T> LinkedListNode<T>::LinkedListNode(LinkedListNode<T>&& other) : next(other.next), data(other.data) {
}

// Move assignment operator
template <typename T> LinkedListNode<T>& LinkedListNode<T>::operator = (LinkedListNode<T>&& other) {
    if (this != &other) {
        this->next = other.getNext();
        this->data = other.getData();
    }
    return *this;
}

#endif /* defined(__CPP_Lists__list__) */
