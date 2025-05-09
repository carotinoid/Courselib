#pragma once
#include <string>

// Forward declaration
class BirdList;

class Bird
{
protected:
	std::string player_name;
	bool is_alive;
	int role; // Role code
	int killMaxCount; // If this bird is AssassinDuck or Duck, this variable is used.
	bool kill; // Check if this bird kill other in this round.
	bool win; // Check if this bird win the game.
public:
	// Constructor and Destructor
	Bird(std::string);
	virtual ~Bird();

	// Given function.
	std::string GetPlayerName() const;

	// This function is a pure virtual function. (neccessary in this assignment)
	virtual void Skill(BirdList*) = 0;

	// The next functions are getters and setters.
	bool IsAlive() const {return is_alive;}
	void die() {is_alive = false;}
	int GetRole() const {return role;}
	void SetKillMaxCount(int k) {killMaxCount = k;}
	bool HasKilled() const {return kill;}
	void ResetKill() { kill = false; }
	void Win() {win = true;}
	bool HasWon() const {return win;}
	void ResetWin() {win = false;}
};


