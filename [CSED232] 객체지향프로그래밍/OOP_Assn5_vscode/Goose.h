#pragma once
#include "Bird.h"

class Goose : public Bird
{
	public:
	// Constructor, Destructor and Skill function
	Goose(std::string);
	~Goose();
	void Skill(BirdList*);
};