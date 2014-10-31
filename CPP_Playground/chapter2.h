//
//  chapter2.h
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/29/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#ifndef __CPP_Playground__chapter2__
#define __CPP_Playground__chapter2__

#include <vector>
#include <set>
#include <functional>
#include <exception>

#include "list.h"

//template <typename T> extern LinkedListNode<T> * create_list(const std::vector<T>& elements);
//template <typename T> extern void enumerate(LinkedListNode<T> * head, const std::function<void(T)> lambda);
//template <typename T> extern LinkedListNode<T> * remove_duplicates_no_stl(LinkedListNode<T> * head);
//template <typename T> extern LinkedListNode<T> * remove_duplicates(LinkedListNode<T> * head);

//#include <vector>
//#include <set>
//#include <functional>
//
template <typename T> LinkedListNode<T> * create_list(const std::vector<T>& elements) {
    LinkedListNode<T> * head = nullptr, * prev = nullptr;
    for (T element: elements) {
        LinkedListNode<T> * node(new LinkedListNode<T>(element));
        if (head == nullptr) {
            head = node;
        }
        if (prev != nullptr) {
            prev->setNext(node);
        }
        prev = node;
    }
    return head;
}

template <typename T> void enumerate(LinkedListNode<T> * head, const std::function<void(T)> lambda) {
    LinkedListNode<T> * node(head);
    for (; node != nullptr; node = node->getNext()) {
        lambda(node->getData());
    }
}

// A version that uses naked pointers and scans ahead for every element
template <typename T> LinkedListNode<T> * remove_duplicates_no_stl(LinkedListNode<T> * head) {
    if (head == nullptr || head->getNext() == nullptr) {
        return head;
    }
    std::vector<LinkedListNode<T> *> deletedNodes;
    
    LinkedListNode<T> * runner1 = head;
    
    try {
        do {
            LinkedListNode<T> * runner2 = runner1->getNext();
            LinkedListNode<T> * prev = runner1;
            while(runner2 != nullptr) {
                if (runner2->getData() == runner1->getData()) {
                    deletedNodes.push_back(runner2);
                    prev->setNext(runner2->getNext());
                } else {
                    prev = runner2;
                }
                runner2 = runner2->getNext();
            }
            runner1 = runner1->getNext();
        } while (runner1 != nullptr);
    } catch(...) {
    }
    
    for (LinkedListNode<T> * deletedNode: deletedNodes) {
        delete deletedNode;
    }
    
    return head;
}

// A version that uses sets
template <typename T> LinkedListNode<T> * remove_duplicates(LinkedListNode<T> * head) {
    if (head == nullptr || head->getNext() == nullptr) {
        return head;
    }
    std::vector<LinkedListNode<T> *> deletedNodes;
    std::set<T> data;
    
    LinkedListNode<T> * runner1 = head;
    LinkedListNode<T> * prev = runner1;
    
    try {
        do {
            if (data.count(runner1->getData()) > 0) {
                prev->setNext(runner1->getNext());
            } else {
                data.insert(runner1->getData());
                prev = runner1;
            }
            if (runner1 != nullptr) {
                runner1 = runner1->getNext();
            }
        } while (runner1 != nullptr);
    } catch(...) {
    }
    
    for (LinkedListNode<T> * deletedNode: deletedNodes) {
        delete deletedNode;
    }
    
    return head;
}

// 2.2: A kth element from the end
template <typename T> LinkedListNode<T> * find_kth_from_the_end(LinkedListNode<T> * head, unsigned int k) {
    LinkedListNode<T> * runnerAhead = head;
    for (unsigned int i = 0; i < k; i++) {
        if (runnerAhead == nullptr) {
            return nullptr;
        }
        runnerAhead = runnerAhead->getNext();
    }
    if (runnerAhead == nullptr) {
        return nullptr;
    }
    LinkedListNode<T> * runnerBehind = head;
    while (runnerAhead != nullptr) {
        runnerAhead = runnerAhead->getNext();
        if (runnerAhead == nullptr) {
            return runnerBehind;
        }
        runnerBehind = runnerBehind->getNext();
    }
    return runnerBehind;
}

// 2.3: Delete a node in the middle of a list, given the pointer to this element
template <typename T> LinkedListNode<T> * delete_in_the_middle(LinkedListNode<T> * node) {
    if (node == nullptr) {
        return nullptr;
    }
    // If it is the last element in the list, the trick will not work
    if (node->getNext() == nullptr) {
        return nullptr;
    }
    // Copy data from the next element to the current one and delete the next element from the list
    auto next = node->getNext();
    node->setData(next->getData());
    node->setNext(next->getNext());
    delete next;
    return node;
}

// 2.4: Partition a list around X
template <typename T> LinkedListNode<T> * partition_around(LinkedListNode<T> * head, T partVal) {
    LinkedListNode<T> * lesserHead = nullptr;
    LinkedListNode<T> * greaterHead = nullptr;
    LinkedListNode<T> * lesserTail = nullptr;
    LinkedListNode<T> * greaterTail = nullptr;
    for (LinkedListNode<T> * node = head; node != nullptr; node = node->getNext()) {
        // partition magic
        if (node->getData() < partVal) {
            if (lesserHead == nullptr) {
                lesserHead = node;
            }
            if (lesserTail != nullptr) {
                lesserTail->setNext(node);
            }
            lesserTail = node;
        } else {
            if (greaterHead == nullptr) {
                greaterHead = node;
            }
            if (greaterTail != nullptr) {
                greaterTail->setNext(node);
            }
            greaterTail = node;
        }
    }
    // concatenate two partitions
    if (lesserTail != nullptr) {
        lesserTail->setNext(greaterHead);
    }
    // make sure we "cut" the second partition
    if (greaterTail != nullptr) {
        greaterTail->setNext(nullptr);
    }
    if (lesserHead == nullptr) {
        lesserHead = greaterHead;
    }
    return lesserHead;
}

// 2.5: You have two numbers represented by a linked list, where each node contains a single digit.
// The digits are stored in reverse order, such that the 1's digit is at the head of the list.
// Write a function that adds the two numbers and returns the sum as a linked list.

template <typename T> T sum_lists(LinkedListNode<T> * list1, LinkedListNode<T> * list2) {
    auto node1 = list1;
    auto node2 = list2;
    T sum = 0;
    T multiplier = 1;
    while (node1 != nullptr) {
        if (node2 == nullptr) {
            throw std::runtime_error("list2 is shorter");
        }
        sum += (node1->getData() + node2->getData()) * multiplier;
        multiplier *= 10;
        node1 = node1->getNext();
        node2 = node2->getNext();
    }
    if (node2 != nullptr) {
        throw std::runtime_error("list1 is shorter");
    }
    return sum;
}

// 2.5: Suppose the digits are stored in forward order. Repeat the above problem.

template <typename T> T sum_reversed_lists(LinkedListNode<T> * list1, LinkedListNode<T> * list2) {
    auto node1 = list1;
    auto node2 = list2;
    T sum = 0;
    while (node1 != nullptr) {
        if (node2 == nullptr) {
            throw std::runtime_error("list2 is shorter");
        }
        sum = sum * 10 + (node1->getData() + node2->getData());
        node1 = node1->getNext();
        node2 = node2->getNext();
    }
    if (node2 != nullptr) {
        throw std::runtime_error("list1 is shorter");
    }
    return sum;
}

// 2.6. Given a circular linked list, implement an algorithm which returns the node at the beginning of the loop.

// N0 - number of nodes before the loop
// Nl - number of nmodes in the loop
// total number of nodes: N = N0 + Nl
// index of the node where the pointers meet:
// - when the p0 reaches the node <N0 + 1> (enters the loop), p1 will pass 2 * N0  + 2 nodes
// - it means p1 will be at the node (((2 * N0 + 2) - N0) mod N1) + N0 = ((N0 + 2) mod N1) + N0
// at any given moment n their positions will be:
template <typename T> bool is_circular(LinkedListNode<T> * head) {
    if (head == nullptr) {
        return false;
    }
    auto p0 = head;
    auto p1 = head;
    while (p0 != nullptr && p1 != nullptr) {
        p1 = p1->getNext();
        if (p1 == nullptr) {
            return false;
        }
        if (p1 == p0) {
            return true;
        }
        if (p1->getNext() == nullptr) {
            return false;
        }
        p1 = p1->getNext();
        if (p1 == p0) {
            return true;
        }
        p0 = p0->getNext();
    }
    return false;
}

template <typename T>
LinkedListNode<T> * find_loop_start(LinkedListNode<T> * head) {
    auto p = head;
    // if the list is NOT circular, it is cheaper to check it in advance than 
    if (!is_circular(head)) {
        return nullptr;
    }
    while (p != nullptr) {
        auto tmpNext = p->getNext();
        p->setNext(nullptr);
        if (!is_circular(tmpNext)) {
            p->setNext(tmpNext);
            return p;
        }
        p->setNext(tmpNext);
        p = tmpNext;
    }
    return nullptr;
}

// 2.7. Implement a function to check if a linked list is a palindrome.
template <typename T>
int list_length(LinkedListNode<T> * head) {
    if (head == nullptr) {
        return 0;
    }
    if (is_circular<T>(head)) {
        return -1;
    }
    int len = 0;
    for (auto node = head; node != nullptr; node = node->getNext(), len++)
        ;
    return len;
}

template <typename T> LinkedListNode<T> * find_kth(LinkedListNode<T> * head, unsigned int k) {
    LinkedListNode<T> * runner = head;
    for (unsigned int i = 0; i < k; i++) {
        if (runner == nullptr) {
            break;
        }
        runner = runner->getNext();
    }
    return runner;
}

// Brute force stuff: constant space, quadratic time
template <typename T>
bool is_palindrome(LinkedListNode<T> * head) {
    if (head == nullptr) {
        return false;
    }
    int len = list_length(head);
    if (len < 0) {
        // detected a loop in the list
        return false;
    }
    for (int i = 0; i < len / 2; i++) {
        auto left = find_kth(head, i);
        auto right = find_kth_from_the_end(head, i);
        if (left->getData() != right->getData()) {
            return false;
        }
    }
    return true;
}

#endif /* defined(__CPP_Playground__chapter2__) */
