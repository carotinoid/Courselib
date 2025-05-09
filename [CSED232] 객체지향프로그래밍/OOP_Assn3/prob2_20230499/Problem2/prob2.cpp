#include <iostream>
#include <limits>
#include "prob2.h" // include the custom header.

void add(OrderedSet* ordered, int v) // The function that add one node in orderedset
{
	if (contains(ordered, v)) return; //prevent duplicate
	Node* newNode = new Node;  // First, make the new node contained argument value v.
	newNode->value = v;
	newNode->next = nullptr;
	if (ordered->m_size == 0)	// If add() is executed at first time, there is not element in set.
	{							// So It can be inserted without any consideration.
		ordered->head->next = newNode;
		ordered->m_size++;
	}
	else // However, there are some elements in element set already,
	{
		Node* now = ordered->head; // 'now' is the pointer that will be point the preceding node before target.
		for (int i = 0; i < ordered->m_size; i++)
		{
			if (now->next->value > v || now->next == nullptr)
			{ // For_each orderedset, "now" find the proper position for new node to be inserted.
				newNode->next = now->next; // and then, insert it. For inserting, we have to change the pointer-links.
				now->next = newNode;
				ordered->m_size++;
				return;
			}
			now = now->next;
		}
		ordered->m_size++; // If New node is the biggest, then insert at last position.
		now->next = newNode;
	}
}

void add(OrderedSet* ordered, const int* arr, int size)
{ // If New node is the biggest, then insert at last position.
	for (int i = 0; i < size; i++) add(ordered, arr[i]);
} // For_each arr, execute add(o, one value)

void remove(OrderedSet* ordered, int index)
{
	Node* now = ordered->head;
	for (int i = 0; i < index; i++)
	{
		now = now->next;
	}
	Node* del = new Node;
	del = now->next;  // 'del' is the target that will be deleted.
	ordered->m_size--; // decrease size of set.
	now->next = now->next->next; // changing the pointer-links
	delete del; // because we use "new" keyword to allocate the memory, "delete' keyword is necessary for prwvent memory leak.
}

int size(OrderedSet* ordered) // This fucntion return the size of set.
{
	return ordered->m_size;
}

bool contains(OrderedSet* ordered, int v) // This is the function that check if 'v' is already in Orderedset.

{
	Node* now = ordered->head; // 'now' has... run like iterator :) 
	bool in = false;			// boolean variable 'in'
	for (int i = 0; i < ordered->m_size; i++)
	{
		now = now->next;
		if (now->value == v) in = true; //if v already exists? then 'in' be true.
	}
	return in;
}

int getValue(OrderedSet* ordered, int idx) 	//This function is used for getting value which positioned at index.
{
	if (idx > ordered->m_size - 1) return INT_MIN; //If argument index is too large, return int min.
	Node* now = ordered->head;
	for (int i = 0; i < idx; i++)
	{
		now = now->next;		// Also... now actives like iterator...?
	}							// so, now points the preceding node before target.
	int val = now->next->value;	// then, return the target's value.
	return val;
}

bool isDup(OrderedSet* ordered, int v) // isDup function is same with contains
{
	return contains(ordered, v);
}