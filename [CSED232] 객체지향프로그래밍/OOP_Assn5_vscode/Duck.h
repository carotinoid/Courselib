#pragma once
#include "Bird.h"

class Duck : public Bird
{
	public:
	// Constructor, Destructor and Skill function
	Duck(std::string);
	~Duck();
	void Skill(BirdList*);
};