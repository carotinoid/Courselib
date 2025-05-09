#pragma once
#include "BirdNode.h"

#include <string>

// Given class.
class BirdList
{
private:
	BirdNode* head;
	BirdNode* tail;
public:
	BirdList();
	~BirdList();

	BirdNode* GetHead() const;
	BirdNode* GetTail() const;
	void AddBirdNode(BirdNode*);
};

