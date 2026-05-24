#pragma once
#include <stdexcept>

using namespace std;

// custom stack using linked list
template <typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* topNode;
    int sz;

public:
    Stack() {
        topNode = nullptr;
        sz = 0;
    }

    // destructor to free memory
    ~Stack() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void push(T val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
        sz++;
    }

    void pop() {
        if (isEmpty())
            throw runtime_error("Runtime error: stack underflow");
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        sz--;
    }

    T top() {
        if (isEmpty())
            throw runtime_error("Runtime error: stack is empty");
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    int size() {
        return sz;
    }
};