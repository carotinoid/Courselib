#pragma once
#include <vector>
#ifndef MULTIHEADLIST_H
#define MULTIHEADLIST_H

/// @brief Node class for MultiHeadList
/// @tparam T type of data to be stored in the node.
/// @details given.
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

/// @brief MultiHeadList class implemented by vector and doubly linked list.
/// @tparam T type of data to be stored in the list.
template <typename T>
class MultiHeadList {
private:
    std::vector<Node<T>*> headList;
public :
    //////////////////////////////////////////
    //////// Inner classes (Iterator) ////////
    //////////////////////////////////////////

    class Iterator {
        public:
            Node<T>* curr;
            // Constructor
            Iterator(Node<T>* node) : curr(node) {}
            // Operator overloading
            // pre-increment
            Iterator& operator++() {
                curr = curr->next;
                return *this;
            }
            // post-increment
            Iterator operator++(int) {
                Iterator temp = curr;
                curr = curr->next;
                return temp;
            }
            // pre-decrement
            Iterator& operator--() {
                curr = curr->prev;
                return *this;
            }
            // post-decrement
            Iterator operator--(int) {
                Iterator temp = curr;
                curr = curr->prev;
                return temp;
            }
            // plus operator
            Iterator& operator+(int n) {
                for(int i = 0; i < n; i++) {
                    curr = curr->next;
                }
                return *this;
            }
            // minus operator
            Iterator& operator-(int n) {
                for(int i = 0; i < n; i++) {
                    curr = curr->prev;
                }
                return *this;
            }
            // not equal operator
            bool operator!=(const Iterator& it) {
                return curr != it.curr;
            }
            // equal operator
            bool operator==(const Iterator& it) {
                return curr == it.curr;
            }
            // dereference, get value operator
            T& operator*() {
                return curr->data;
            }
    };
    class ReverseIterator{
        public:
            Node<T>* curr;
            // Constructor
            ReverseIterator(Node<T>* node) : curr(node) {}
            // Operator overloading
            // pre-increment
            ReverseIterator& operator++() {
                curr = curr->prev;
                return *this;
            }
            // post-increment
            ReverseIterator operator++(int) {
                ReverseIterator temp = curr;
                curr = curr->prev;
                return temp;
            }
            // pre-decrement
            ReverseIterator& operator--() {
                curr = curr->next;
                return *this;
            }
            // post-decrement
            ReverseIterator operator--(int) {
                ReverseIterator temp = curr;
                curr = curr->next;
                return temp;
            }
            // plus operator
            ReverseIterator& operator+(int n) {
                for(int i = 0; i < n; i++) {
                    curr = curr->prev;
                }
                return *this;
            }
            // minus operator
            ReverseIterator& operator-(int n) {
                for(int i = 0; i < n; i++) {
                    curr = curr->next;
                }
                return *this;
            }
            // not equal operator
            bool operator!=(const ReverseIterator& it) {
                return curr != it.curr;
            }
            // equal operator
            bool operator==(const ReverseIterator& it) {
                return curr == it.curr;
            }
            // dereference, get value operator
            T& operator*() {
                return curr->data;
            }
    };

public:
    ////////////////////////////////////
    //////// Member functions //////////
    ////////////////////////////////////

    /// @brief Get the number of heads in the vector.
    /// @return the number of heads
    int headSize() {
        return headList.size();
    }

    /// @brief If head Idx is negative or greator than the number of heads, the new head is created at the end of the list. Otherwise, add a new node to the end of the headIdx-th head.
    /// @param data data to be added.
    /// @param headIdx where the data will be added.
    void push_back(const T& data, int headIdx=-1) {
        if(headIdx == -1 or headIdx >= headSize()) {
            headList.push_back(new Node<T>(data));
        } else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* tail = headList[headIdx];
            while(tail->next != nullptr) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        }
    }

    /// @brief If headIdx is negative or greater than the number of heads, the new head is created at the end of the list. Otherwise, add a new node to the front of the headIdx-th head.
    /// @param data data to be added.
    /// @param headIdx where the data will be added.
    void push_front(const T& data, int headIdx=-1) {
        if(headIdx == -1 or headIdx >= headSize()) {
            headList.push_back(new Node<T>(data));
        } else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* head = headList[headIdx];
            head->prev = newNode;
            newNode->next = head;
            headList[headIdx] = newNode;
        }
    }

    /// @brief Insert a new node with data in front of iterator pos.
    /// @details You cannot insert at the end of the list because the end iterator is nullptr.
    /// @param pos iterator to insert the data.
    /// @param data data to be inserted.
    void insert(Iterator pos, const T& data) {
        if(pos.curr == nullptr) return;
        if(pos.curr->prev == nullptr) {
            Node<T>* newNode = new Node<T>(pos.curr->data);
            Node<T>* nextNode = pos.curr->next;
            pos.curr->data = data;
            pos.curr->next = newNode;
            newNode->prev = pos.curr;
            newNode->next = nextNode;
            if(nextNode != nullptr) nextNode->prev = newNode;
        } else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* prevNode = pos.curr->prev;
            Node<T>* nextNode = pos.curr;
            prevNode->next = newNode;
            newNode->prev = prevNode;
            newNode->next = nextNode;
            nextNode->prev = newNode;
        }
    }

    /// @brief Remove the last data of the headIdx-th head.
    /// @param headIdx the index of the head to remove the data.
    void pop_back(int headIdx) {
        Node<T>* head = headList[headIdx];
        Node<T>* tail = headList[headIdx];
        while(tail->next != nullptr) {
            tail = tail->next;
        }
        if(head == tail) {
            delete tail;
            headList.erase(headList.begin() + headIdx);
        } else {
            tail->prev->next = nullptr;
            delete tail;
        }
    }

    /// @brief Remove the first data of the headIdx-th head.
    /// @param headIdx the index of the head to remove the data
    void pop_front(int headIdx) {
        Node<T>* head = headList[headIdx];
        Node<T>* tail = headList[headIdx];
        while(tail->next != nullptr) {
            tail = tail->next;
        }
        if(head == tail) {
            delete head;
            headList.erase(headList.begin() + headIdx);
        } else {
            headList[headIdx] = head->next;
            head->next->prev = nullptr;
            delete head;
        }
    }

    /// @brief Merge the frontHeadIdx-th head and the backHeadIdx-th head.
    /// @details The frontHeadIdx-th head is connected to the backHeadIdx-th head, and the backHeadIdx-th head is removed.
    /// @param frontHeadIdx the index of the head to be merged in front.
    /// @param backHeadIdx the index of the head to be merged in back.
    void merge(int frontHeadIdx, int backHeadIdx) {
        // Find the tail of frontHeadIdx-th head
        Node<T>* frontTail = headList[frontHeadIdx];
        while(frontTail->next != nullptr) {
            frontTail = frontTail->next;
        }
        // Connect
        frontTail->next = headList[backHeadIdx];
        headList[backHeadIdx]->prev = frontTail;
        // Remove backHeadIdx-th head
        headList.erase(headList.begin() + backHeadIdx);
    }

    /// @brief Erase the data from the headIdx-th head, and seperate the head if the pos is in the middle.
    /// @param data data to be erased.
    /// @param targetHeadIdx the index of the head to erase the data.
    /// @return true if the data is erased, false otherwise.
    bool erase(const T& data, int targetHeadIdx) {
        bool success = false;
        // Finding target
        Node<T>* target = headList[targetHeadIdx];
        while(target != nullptr) {
            if(target->data == data) {
                success = true;
                break;
            }
            target = target->next;
        }
        // If the target is not found, return false.
        if(!success) return false;

        // If the target is found, erase the target.
        Node<T>* head = headList[targetHeadIdx];
        Node<T>* tail = headList[targetHeadIdx];
        while(tail->next != nullptr) {
            tail = tail->next;
        }
        // Case 1. If there is only one node in the head.
        // Delete the node and remove the head from the headList(vector).
        if(head == target and tail == target) {
            delete target;
            headList.erase(headList.begin() + targetHeadIdx);
        // Case 2. If the target is the head.
        // Remove the target and next node becomes the head.
        } else if(target == head) {
            headList[targetHeadIdx] = head->next;
            head->next->prev = nullptr;
            delete target;
        // Case 3. If the target is the tail.
        // Remove the target and the previous node becomes the tail.
        } else if(target == tail) {
            tail->prev->next = nullptr;
            delete target;
        // Case 4. If the target is in the middle.
        // Remove the target and seperate the previous list and the next list.
        } else {
            Node<T>* prevNode = target->prev;
            Node<T>* nextNode = target->next;
            prevNode->next = nullptr;
            delete target;

            // Make new doubly linked list
            nextNode->prev = nullptr;
            push_back(nextNode->data);
            while(nextNode->next != nullptr) {
                Node<T>* temp = nextNode;
                nextNode = nextNode->next;
                push_back(nextNode->data, headList.size() - 1);
                delete temp;
            }
        }
        return true;
    }
    /// @brief Erase the data where the iterator points, and seperate the head if the pos is in the middle.
    /// @param pos iterator where the data will be erased.
    /// @return true if the data is erased, false otherwise.
    bool erase(Iterator pos) {
        // If the iterator is nullptr, return false.
        if(pos.curr == nullptr) return false;

        // Case 1. If the head is the only node.
        // Delete the node and remove the head from the headList(vector).
        if(pos.curr->prev == nullptr and pos.curr->next == nullptr) {
            for(int i = 0; i < headList.size(); i++) {
                if(headList[i] == pos.curr) {
                    headList.erase(headList.begin() + i);
                    delete pos.curr;
                    break;
                }
            }
        }
        // Case 2. If the target is the head.
        // Remove the target and next node becomes the head.
        else if(pos.curr->prev == nullptr) {
            for(int i = 0; i < headList.size(); i++) {
                if(headList[i] == pos.curr) {
                    headList[i] = pos.curr->next;
                    headList[i]->prev = nullptr;
                    delete pos.curr;
                    break;
                }
            }
        }
        // Case 3. If the target is the tail.
        // Remove the target and the previous node becomes the tail.
        else if(pos.curr->next == nullptr) {
            pos.curr->prev->next = nullptr;
            delete pos.curr;
        }
        // Case 4. If the target is in the middle.
        // Remove the target and seperate the previous list and the next list.
        else {
            Node<T>* prevNode = pos.curr->prev;
            Node<T>* nextNode = pos.curr->next;
            prevNode->next = nullptr;
            delete pos.curr;

            // Make new doubly linked list
            nextNode->prev = nullptr;
            push_back(nextNode->data);
            while(nextNode->next != nullptr) {
                Node<T>* temp = nextNode;
                nextNode = nextNode->next;
                push_back(nextNode->data, headList.size() - 1);
                delete temp;
            }
        }
        return true;
    }

    //////////////////////////////////////
    //////// Iterator functions //////////
    //////////////////////////////////////

    /// @brief Return the beginning of the headIdx-th head.
    /// @param headIdx The index of the head to get the beginning.
    /// @return iterator pointing to the beginning of the headIdx-th head.
    Iterator begin(int headIdx) {
        return Iterator(headList[headIdx]);
    }

    /// @brief Return nullptr
    /// @return nullptr
    Iterator end() {
        return Iterator(nullptr);
    }

    /// @brief Return the reverse beginning of the headIdx-th head.
    /// @param headIdx The index of the head to get the reverse beginning.
    /// @return iterator pointing to the reverse beginning of the headIdx-th head.
    ReverseIterator rbegin(int headIdx) {
        Node<T>* tail = headList[headIdx];
        while(tail->next != nullptr) {
            tail = tail->next;
        }
        return ReverseIterator(tail);
    }

    /// @brief Return nullptr
    /// @return nullptr
    ReverseIterator rend() {
        return ReverseIterator(nullptr);
    }
};

#endif