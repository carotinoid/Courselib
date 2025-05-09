#pragma once
#include "Bird.h"

class AssassinDuck : public Bird
{
	private:
	const int AssassinateMaxCount = 2;
	int assassinate_count;
	public:
	// Counstructor, Destructor, Skill function.
	AssassinDuck(std::string);
	~AssassinDuck();
	void Skill(BirdList*);
};
