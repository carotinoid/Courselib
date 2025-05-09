#pragma once
struct Node //implementation of Node. Node is the form of singly-linked list, and it is contain value and next Node pointer.
{
	int value = 0;
	Node* next = nullptr;
};

struct OrderedSet	//implementation of OrderedList. It has m_size, the # of elements and head node pointer
{					//Actually, header is not first element, the next node pointed by header is first element.
	int m_size = 0;
	Node* head = new Node;
};

// prototype
void add(OrderedSet* ordered, int v);
void add(OrderedSet* ordered, const int* arr, int size);
void remove(OrderedSet* ordered, int index);
int size(OrderedSet* ordered);
bool contains(OrderedSet* ordered, int v);
int getValue(OrderedSet* ordered, int idx);
bool isDup(OrderedSet* ordered, int v);