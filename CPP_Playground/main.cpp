//
//  main.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/14/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include <iostream>
#include <exception>
#include <utility>

#include "list.h"
//#include "list.cpp"
#include "chapter2.h"
#include "chapter2.cpp"

//template class LinkedListNode<int>;
//extern template LinkedListNode<int> * create_list(const std::vector<int>& elements);
//extern template void enumerate(LinkedListNode<int> * head, const std::function<void(int)> lambda);
//extern template LinkedListNode<int> * remove_duplicates_no_stl(LinkedListNode<int> * head);
//extern template LinkedListNode<int> * remove_duplicates(LinkedListNode<int> * head);

int test_chapter2(int argc, const char * argv[]) {
    auto listPrinter = [] (int x) {std::cout << x << std::endl;};
    // 2.1
    {
        std::vector<int> v({1, 2, 3, 1, 2, 3, 1});
        std::cout << "Problem 2.1, without sets:\n";
        LinkedListNode<int> * head = create_list<int>(v);
        std::cout << "Before: \n";
        enumerate<int>(head, listPrinter);
        head = remove_duplicates_no_stl<int>(head);
        std::cout << "After: \n";
        enumerate<int>(head, listPrinter);
        std::cout << "Problem 2.1, with sets:\n";
        head = create_list<int>(v);
        std::cout << "Before: \n";
        enumerate<int>(head, listPrinter);
        head = remove_duplicates<int>(head);
        std::cout << "After: \n";
        enumerate<int>(head, listPrinter);
    }
    // 2.2
    {
        std::vector<int> v({5, 4, 3, 2, 1, 0});
        LinkedListNode<int> * head = create_list<int>(v);
        auto node = find_kth_from_the_end<int>(head, 0);
        std::cout << "0th from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 1);
        std::cout << "1st from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 2);
        std::cout << "2nd from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 3);
        std::cout << "3rd from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 5);
        std::cout << "5th from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 6);
        std::cout << "6th from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
        node = find_kth_from_the_end<int>(head, 7);
        std::cout << "7th from the end: " << (node != nullptr ? node->getData() : -1) << std::endl;
    }
    // 2.3
    {
        std::cout << "Deleting node with val = 3:\n";
        std::vector<int> v({0, 1, 2, 3, 4, 5, 6});
        LinkedListNode<int> * head = create_list<int>(v);
        auto node = head;
        while (node->getData() < 3) {
            node = node->getNext();
        }
        node = delete_in_the_middle(node);
        enumerate<int>(head, listPrinter);
    }
    
    // 2.4
    {
        std::cout << "Partitioning around 4:\n";
        std::vector<int> v({0, 4, 1, 5, 2, 6, 3, 7});
        //        std::vector<int> v({4, 7});
        //        std::vector<int> v({0, 1});
        LinkedListNode<int> * head = create_list<int>(v);
        head = partition_around<int>(head, 4);
        enumerate<int>(head, listPrinter);
    }
    
    // 2.5
    {
        std::cout << "Adding the lists:\n";
        std::vector<int> v1({1, 0, 2}), v2({0, 2, 0});
        LinkedListNode<int> * l1(create_list<int>(v1)), * l2(create_list<int>(v2));
        auto inlineListPrinter = [] (int x) {std::cout << x;};
        int sum = sum_lists<int>(l1, l2);
        std::cout << "The sum of ";
        enumerate<int>(l1, inlineListPrinter);
        std::cout << " and ";
        enumerate<int>(l2, inlineListPrinter);
        std::cout << " is " << sum << std::endl;
        sum = sum_reversed_lists(l1, l2);
        std::cout << "Reversed sum: " << sum << std::endl;
    }
    {
        try {
            std::cout << "Adding the lists:\n";
            std::vector<int> v1({1, 0, 2}), v2({0, 2});
            LinkedListNode<int> * l1(create_list<int>(v1)), * l2(create_list<int>(v2));
            auto inlineListPrinter = [] (int x) {std::cout << x;};
            int sum = sum_lists<int>(l1, l2);
            std::cout << "The sum of ";
            enumerate<int>(l1, inlineListPrinter);
            std::cout << " and ";
            enumerate<int>(l2, inlineListPrinter);
            std::cout << " is " << sum << std::endl;
            sum = sum_reversed_lists(l1, l2);
            std::cout << "Reversed sum: " << sum << std::endl;
        } catch(const std::runtime_error& err) {
            std::cout << "Snafu in progress: " << err.what() << std::endl;
        }
    }
    // 2.6
    {
        std::cout << "Looking for loops:\n";
        std::vector<char> v({'a', 'b', 'c', 'd', 'e'});
        auto head = create_list(v);
        auto node = head;
        while (node->getData() != 'c') {
            node = node->getNext();
        }
        auto tail = head;
        while (tail->getNext() != nullptr) {
            tail = tail->getNext();
        }
        tail->setNext(node);
        auto looper = find_loop_start(head);
        if (looper != nullptr) {
            std::cout << "The loop: " << looper->getData() << std::endl;
        } else {
            std::cout << "Loop not found\n";
        }
        tail->setNext(nullptr);
        looper = find_loop_start(head);
        if (looper != nullptr) {
            std::cout << "The loop: " << looper->getData() << std::endl;
        } else {
            std::cout << "Loop not found\n";
        }
    }
    {
        std::vector<char> v({'a'});
        auto head = create_list(v);
        head->setNext(head);
        auto looper = find_loop_start(head);
        if (looper != nullptr) {
            std::cout << "The loop: " << looper->getData() << std::endl;
        } else {
            std::cout << "Loop not found\n";
        }
    }

    // 2.7
    {
        std::vector<char> v({'b', 'a', 'c', 'a', 'b'});
        auto head = create_list(v);
        auto inlineListPrinter = [] (char x) {std::cout << x;};
        std::cout << "Is ";
        enumerate<char>(head, inlineListPrinter);
        std::cout << " a palindrome? " << is_palindrome(head) << std::endl;
    }
    {
        std::vector<char> v({'b'});
        auto head = create_list(v);
        auto inlineListPrinter = [] (char x) {std::cout << x;};
        std::cout << "Is ";
        enumerate<char>(head, inlineListPrinter);
        std::cout << " a palindrome? " << is_palindrome(head) << std::endl;
    }
    {
        std::vector<char> v({'b', 'a', 'a', 'b'});
        auto head = create_list(v);
        auto inlineListPrinter = [] (char x) {std::cout << x;};
        std::cout << "Is ";
        enumerate<char>(head, inlineListPrinter);
        std::cout << " a palindrome? " << is_palindrome(head) << std::endl;
    }
    {
        std::vector<char> v({'b', 'a', 'c', 'a'});
        auto head = create_list(v);
        auto inlineListPrinter = [] (char x) {std::cout << x;};
        std::cout << "Is ";
        enumerate<char>(head, inlineListPrinter);
        std::cout << " a palindrome? " << is_palindrome(head) << std::endl;
    }
    {
        std::vector<char> v({'b', 'a', 'c', 'a', 'c'});
        auto head = create_list(v);
        auto inlineListPrinter = [] (char x) {std::cout << x;};
        std::cout << "Is ";
        enumerate<char>(head, inlineListPrinter);
        std::cout << " a palindrome? " << is_palindrome(head) << std::endl;
    }

    return 0;
}

