#pragma once
#include <string>

class BirdList;

class Bird
{
protected:
	std::string player_name;
public:
	Bird();
	virtual ~Bird();
	std::string GetPlayerName() const;
	virtual void Skill(BirdList*)=0;
};

