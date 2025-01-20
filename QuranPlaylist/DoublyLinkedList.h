//
// Created by Mahmoud Elshafei on 11/11/2024.
//

#ifndef QURANPLAYLIST_DOUBLYLINKEDLIST_H
#define QURANPLAYLIST_DOUBLYLINKEDLIST_H

#include <iostream>
#include <unordered_map>

template<class T>
struct Node {
    T data{};
    Node *next{};
    Node *prev{};

    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};


template<class T>
class DoublyLinkedList {
    Node<T> *head{};
    Node<T> *tail{};
    size_t length{};


    //// Helper Function to help me in Debug my list and catch issues
    void blackBoxDebugging() { // O(1) time - O(1) memory
        if (length > 0) {
            if (!head)
                throw std::runtime_error("The Length > 0 and the head is null..\n");
            if (!tail)
                throw std::runtime_error("The Length > 0 and the tail is null..\n");
            if (head->prev)
                throw std::runtime_error("The Length > 0 and the head->prev is not null..\n");
            if (tail->next)
                throw std::runtime_error("The Length > 0 and the tail->next is not null..\n");
        } else {
            if (head)
                throw std::runtime_error("The Length = 0 and the head is not null..\n");
            if (tail)
                throw std::runtime_error("The Length = 0 and the tail is not null..\n");

        }
    }

    // utility function to link two nodes
    void link(Node<T> *first, Node<T> *second) { // O(1) time - O(1) memory
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }


public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}; // O(1) time - O(1) memory
    explicit DoublyLinkedList(T val) { // O(1) time - O(1) memory
        insertFront(val);
    }
    DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), length(0) {
        Node<T>* cur = other.head;
        while (cur) {
            insertEnd(cur->data);
            cur = cur->next;
        }
    }
    DoublyLinkedList& operator=(const DoublyLinkedList<T>& other) {
        if (this == &other)
            return *this;

        clear();

        Node<T>* cur = other.head;
        while (cur) {
            insertEnd(cur->data);
            cur = cur->next;
        }
        return *this;
    }
    bool operator==(const DoublyLinkedList<T>& other) {
        // If lengths are different, the lists are not equal
        if (length != other.length)
            return false;

        // Traverse both lists and compare data
        Node<T>* current = head;
        Node<T>* otherCurrent = other.head;
        while (current && otherCurrent) {
            if (current->data != otherCurrent->data) { // This assumes operator== is defined for T
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        // If both lists are traversed completely and data matches, they are equal
        return true;
    }

    ~DoublyLinkedList() { // O(n) time - O(1) memory
        clear();
    }

    void insertFront(T val) { // O(1) time - O(1) memory
        auto *newNode = new Node<T>(val);
        if (!length) {
            head = tail = newNode;
        } else {
            link(newNode, head);
            head = newNode;
        }
        length++;
        blackBoxDebugging();
    }

    void insertEnd(T val) { // O(1) time - O(1) memory
        auto *newNode = new Node<T>(val);
        if (!length) {
            tail = head = newNode;
        } else {
            link(tail, newNode);
            tail = newNode;
        }
        length++;
        blackBoxDebugging();
    }

    void insert(T val, size_t idx) { // O(n) time - O(1) memory
        if (idx > length)
            throw std::runtime_error("The idx is out of bounds..\n");

        if (!length || idx == 0) { insertFront(val); }
        else if (length == idx) { insertEnd(val); }
        else {
            size_t cur_idx = 0;
            for (Node<T> *cur = head; cur; cur_idx++, cur = cur->next) {
                if (cur_idx + 1 == idx) {
                    auto *newNode = new Node<T>(val);
                    auto *curNode = cur;
                    cur = cur->next;
                    link(curNode, newNode);
                    link(newNode, cur);
                    break;
                }
            }
            length++;
            blackBoxDebugging();
        }
    }

    void removeFront() { // o(1) time - o(1) memory
        if (!length)
            throw std::runtime_error("No data to remove!!\n");
        Node<T> *deleted = head;
        if (length == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete deleted;
        length--;
        blackBoxDebugging();
    }

    void removeEnd() { // o(1) time - o(1) memory
        if (!length)
            throw std::runtime_error("No data to remove!!\n");

        Node<T> *deleted = tail;
        if (length == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete deleted;
        length--;
        blackBoxDebugging();
    }

    // remove the first node with this val
    void remove(T val) {  // o(n) time - o(1) memory
        if (!length)
            throw std::runtime_error("No data to remove!!\n");

        if (head->data == val)
            return removeFront(), void();
        else if (tail->data == val)
            return removeEnd(), void();
        else {
            for (Node<T> *cur = head; cur; cur = cur->next) {
                if (cur->data == val) {
                    Node<T> *prev = cur->prev;
                    Node<T> *next = cur->next;
                    link(prev, next);
                    delete cur;
                    length--;
                    blackBoxDebugging();
                    return;
                }
            }
        }
        std::cout << "This Value doesn't exist..\n";
    }

    size_t search(T val) const { // o(n) time - o(1) memory
        size_t idx = 0;
        for (Node<T> *cur = head; cur; idx++, cur = cur->next)
            if (cur->data == val)
                return idx;

        return -1;
    }

    Node<T>* find(T val) const { // o(n) time - o(1) memory
        for (Node<T> *cur = head; cur; cur = cur->next)
            if (cur->data == val)
                return cur;

        return nullptr;
    }

    void remove_duplicates() { // O(n) time - O(1) memory
        if (length <= 1)
            return;

        std::unordered_map<T, bool> freq;
        Node<T> *prev = nullptr;
        Node<T> *cur = head;
        while (cur) {
            if (freq[cur->data]) {
                Node<T> *deleted = cur;
                cur = cur->next;
                if (prev)
                    prev->next = cur;
                else
                    head = cur;
                delete deleted;
                length--;
            } else {
                freq[cur->data] = true;
                prev = cur;
                cur = cur->next;
            }
        }
        tail = prev;
        if (tail)
            tail->next = nullptr;
        blackBoxDebugging();
    }

    Node<T>* getHead() { // O(1) time - O(1) memory
        return head;
    }

    Node<T>* getTail() { // O(1) time - O(1) memory
        return tail;
    }

    size_t size() const { // O(1) time - O(1) memory
        return length;
    }

    bool isEmpty() const { // O(1) time - O(1) memory
        return length == 0;
    }

    // clear all the list
    void clear() { // O(n) time - O(1) memory
        Node<T> *cur = head;
        while (cur) {
            Node<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        length = 0;

//        recursion may cause some issues such as stack overflow with a large list
//        if (!cur)
//            return;
//        clear(cur->next);
//        delete cur;
    }

    void print() const { // O(n) time - O(1) memory
        for (Node<T> *cur = head; cur; cur = cur->next)
            std::cout << cur->data << " \n"[cur->next == nullptr];
    }

    void print_reversed() const { // O(n) time - O(1) memory
        for (Node<T> *cur = tail; cur; cur = cur->prev)
            std::cout << cur->data << " \n"[cur->prev == nullptr];
    }
};

#endif //QURANPLAYLIST_DOUBLYLINKEDLIST_H
