#include "BirdList.h"

#include "Bird.h"
#include "Goose.h"

BirdList::BirdList() {
}

BirdList::~BirdList() {
}

BirdNode* BirdList::GetHead() const {
	return this->head;
}

BirdNode* BirdList::GetTail() const {
	return this->tail;
}

void BirdList::AddBirdNode(BirdNode*) {
}