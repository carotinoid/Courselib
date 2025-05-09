#include "BirdNode.h"

// comments are in the header file

BirdNode::BirdNode() {
	this->bird = NULL;
	this->next = NULL;
}

BirdNode::BirdNode(Bird* bird) {
	this->bird = bird;
	this->next = NULL;
}

BirdNode::~BirdNode() {
	delete this->bird;
}

void BirdNode::SetBird(Bird* bird) {
	this->bird = bird;
}

void BirdNode::SetNext(BirdNode* next) {
	this->next = next;
}

Bird* BirdNode::GetBird() const{
	return this->bird;
}

BirdNode* BirdNode::GetNext() const{
	return this->next;
}