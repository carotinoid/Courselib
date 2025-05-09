#include "Bird.h"
// BirdList is used to implement Bird's Skill, but Skills are not implemented in Bird.cpp. (pure virtual function)
// #include "BirdList.h"
#include <string>
#include <iostream>

// Constructor
Bird::Bird(std::string player_name) : player_name(player_name) {
	is_alive = true;
	win = false;
	kill = false;
}

// Destructor
Bird::~Bird() {
}

// Given function.(getter)
std::string Bird::GetPlayerName() const{
	return this->player_name;
}