#include "BirdList.h"

#include "Bird.h"

// Constructor
BirdList::BirdList() {
	this->head = NULL;
	this->tail = NULL;
}

// Destructor
BirdList::~BirdList() {
	BirdNode* current = this->head;
	while(current != NULL) {
		BirdNode* next = current->GetNext();
		delete current;
		current = next;
	}
}

BirdNode* BirdList::GetHead() const {
	return this->head;
}

BirdNode* BirdList::GetTail() const {
	return this->tail;
}

// AddBirdNode
void BirdList::AddBirdNode(BirdNode* node) {
	// If the list is empty, set the head and tail to the new node
	if(this->head == NULL) {
		this->head = node;
		this->tail = node;
	} else {
		// Otherwise, add the new node to the end of the list
		this->tail->SetNext(node);
		this->tail = node;
	}
}