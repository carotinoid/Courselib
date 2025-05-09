#pragma once

#include "Bird.h"

class MorticianGoose : public Bird
{
	public:
	// Constructor, Destructor and Skill function
	MorticianGoose(std::string);
	~MorticianGoose();
	void Skill(BirdList*);
};