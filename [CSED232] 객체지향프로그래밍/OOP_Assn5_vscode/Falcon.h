#pragma once
#include "Bird.h"

class Falcon : public Bird
{
	public:
	// Constructor, Destructor and Skill function
	Falcon(std::string);
	~Falcon();
	void Skill(BirdList*);
};