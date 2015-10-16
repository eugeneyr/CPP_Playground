//
//  chapter3.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/31/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <memory>
#include <forward_list>
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

template <typename T> class StackedQueue {
    std::stack<T> sideA;
    std::stack<T> sideB;
    std::recursive_timed_mutex mutex;
    std::condition_variable_any cond;
public:
    void add(T& value);
    T get();
};

template <typename T> void StackedQueue<T>::add(T& value) {
    std::unique_lock<std::recursive_timed_mutex> lock(mutex);
    sideA.push(value);
    lock.unlock();
    cond.notify_one();
}

template <typename T> T StackedQueue<T>::get() {
    std::unique_lock<std::recursive_timed_mutex> lock(mutex);
    while (sideA.empty() && sideB.empty()) {
        cond.wait(lock);
    }
    if (sideB.empty()) {
        while (!sideA.empty()) {
            sideB.push(sideA.top());
            sideA.pop();
        }
    }
    T value = sideB.top();
    sideB.pop();
    return value;
}

StackedQueue<int> queue;

std::recursive_timed_mutex mux;
bool stop = false;

void sends() {
    for (int i = 0; i < 100; i++) {
        queue.add(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    int i = -1;
    queue.add(i);
    queue.add(i);
}

void receives() {
    while (!stop) {
        std::unique_lock<std::recursive_timed_mutex> lock(mux);
        int i = queue.get();
        if (i < 0) {
            stop = true;
        } else {
            std::cout << i << std::endl;
        }
    }
}

void test_stacked_queue() {
    std::thread sender(sends), receiver1(receives), receiver2(receives);
    sender.join();
    receiver1.join();
    receiver2.join();
}

// 3.6. Write a program to sort a stack in ascending order (with biggest items on top).
// You may use at most one additional stack to hold items, but you may not copy the elements
// into any other data structure (such as an array).
// The stack supports the following operations: push, pop, peek, and isEmpty.
void sort_stack_with_stack(std::stack<int>& data) {
    std::stack<int> aux;
    if (data.empty()) {
        return;
    }
    int size = 0;
    bool firstRun = true;
    int sortedSize = 0;
    
    do {
        int min = data.top();
        while (!data.empty()) {
            int element = data.top();
            if (element < min) {
                min = element;
            }
            data.pop();
            if (firstRun) {
                size++;
            }
            aux.push(element);
        }
        firstRun = false;
        bool foundMin = false;
        for (int i = 0; i < size - sortedSize; i++) {
            int element = aux.top();
            aux.pop();
            if (element != min) {
                data.push(element);
            } else if (foundMin) {
                data.push(element);
            } else {
                foundMin = true;
            }
        }
        aux.push(min);
        sortedSize++;
    } while (sortedSize < size);
    // at this point, all elements in the aux stack should be sorted
    while (!aux.empty()) {
        int element = aux.top();
        aux.pop();
        data.push(element);
    }
}

void test_sort_stack() {
    std::stack<int> data({3, 2, 4, 2, 7, 1, 10});
    sort_stack_with_stack(data);
    while (!data.empty()) {
        std::cout << data.top() << std::endl;
        data.pop();
    }
}

// 3.7. An animal shelter holds only dogs and cats, and operates on a strictly "first in, first out" basis.
// People must adopt either the "oldest" (based on arrival time) of all animals at the shelter, or they can select
// whether they would prefer a dog or a cat (and will receive the oldest animal of that type).
// They cannot select which specificanimal they would like. Create the data structures to maintain
// this system and implement operations such as enqueue, dequeueAny, dequeueDog and dequeueCat.
// You may use the built-in LinkedList data structure.
struct Animal {
    std::string name;

    Animal() {
    }
    
    Animal(const Animal& otherAnimal) {
        name = otherAnimal.name;
    }
    
    Animal(Animal& otherAnimal) {
        name = otherAnimal.name;
    }
    
    Animal(std::string& name) {
        this->name = name;
    }

    Animal(const std::string& name) {
        this->name = name;
    }

    virtual ~Animal() {
        std::cout << "Animal " << this->name << " is dead\n";
    }
};

typedef enum { Tabby, Siamese, Angora, Persian } CatBreed;

typedef enum { Bulldog, GoldenRetriever, Rottweiller, Shepard, Chihuaua } DogBreed;

struct Cat : Animal {
    CatBreed breed;

    Cat() : Animal("") {
    }
    
    Cat(std::string& name, CatBreed& breed) : Animal(name) {
        this->breed = breed;
    }
    
    Cat(const Cat& otherCat) : Animal(otherCat.name) {
        breed = otherCat.breed;
    }

    Cat(Cat& otherCat) : Animal(otherCat.name) {
        this->breed = otherCat.breed;
    }

    virtual ~Cat() {
        std::cout << "Cat " << name << " is dead\n";
    }
};

struct Dog : Animal {
    DogBreed breed;

    Dog() : Animal("") {
    }
        
    Dog(const Dog& otherDog) : Animal(otherDog.name) {
        breed = otherDog.breed;
    }
    
    Dog(Dog& otherDog) : Animal(otherDog.name) {
        breed = otherDog.breed;
    }

    Dog(std::string& name, DogBreed& breed) : Animal(name) {
        this->breed = breed;
    }
    
    virtual ~Dog() {
        std::cout << "Dog " << name << " is dead\n";
    }
};

class ShelterQueue {
    std::forward_list<Animal*> queue;
public:
    void enqueue(Animal* animal);
    Animal* dequeueAny();
    Dog* dequeueDog();
    Cat* dequeueCat();
};

void ShelterQueue::enqueue(Animal* animal) {
    queue.insert_after(queue.end(), animal);
}

Animal* ShelterQueue::dequeueAny() {
    if (queue.empty()) {
        return nullptr;
    }
    Animal* ptr = *queue.begin();
    queue.pop_front();
    return ptr;
}

Dog* ShelterQueue::dequeueDog() {
    for (Animal* ptr : queue) {
        if (typeid(*ptr) == typeid(Dog)) {
            queue.remove(ptr);
            return dynamic_cast<Dog*>(ptr);
        }
    }
    return nullptr;
}

Cat* ShelterQueue::dequeueCat() {
    for (Animal* ptr : queue) {
        if (typeid(*ptr) == typeid(Cat)) {
            queue.remove(ptr);
            return dynamic_cast<Cat*>(ptr);
        }
    }
    return nullptr;
}


void test_animal_shelter() {
    ShelterQueue queue;
    std::string name("Tom");
    CatBreed breed(Tabby);
    Animal* cat = new Cat(name, breed);
    queue.enqueue(cat);
    cat = new Cat(name, breed);
    queue.enqueue(cat);
    name = std::string("Myrcella");
    breed = CatBreed::Persian;
    cat = new Cat(name, breed);
    queue.enqueue(cat);

}

/*
int main(int argc, char ** argv) {
    //test_three_stacks();
    //test_min_stack();
    //test_set_of_stacks();
    // test_set_of_stacks_popAt();
    //test_towers_of_hanoi();
    // test_stacked_queue();
    //test_sort_stack();
    test_animal_shelter();
    return 0;
}
*/