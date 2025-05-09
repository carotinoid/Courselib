#pragma once
#ifndef MULTIHEADLIST_H
#define MULTIHEADLIST_H

struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

class MultiHeadList {
private:
    vector<Node<T>*> headList;
public :
    class Iterator {};
    class ReverseIterator{};

public:
    int headSize() {}
    void push_back(const T& data, int headIdx=-1) {}
    void push_front(const T& data, int headIdx=-1) {}
    void insert(Iterator pos, const T& data) {}
    void pop_back(int headIdx) {}
    void pop_front(int headIdx) {}
    void merge(int frontHeadIdx, int backHeadIdx) {}
    bool erase(const T& data, int targetHeadIdx) {}
    bool erase(Iterator pos) {}

    Iterator begin(int headIdx) {}
    Iterator end() {}
    ReverseIterator rbegin(int headIdx) {}
    ReverseIterator rend() {}
};

#endif