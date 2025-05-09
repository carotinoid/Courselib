#pragma once
#include "Bird.h"

class Dodo : public Bird
{
	public:
	// Constructor, Destructor and Skill function
	Dodo(std::string);
	~Dodo();
	void Skill(BirdList*);
};