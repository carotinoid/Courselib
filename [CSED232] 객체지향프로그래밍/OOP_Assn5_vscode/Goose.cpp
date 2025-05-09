#include "Goose.h"

#include <iostream>

// Constructor
Goose::Goose(std::string player_name) : Bird(player_name) {
	role = 5;
}

// Destructor
Goose::~Goose() {

}

// Skill function
void Goose::Skill(BirdList*) {
	std::cout << "당신은 능력이 없는 조류입니다." << std::endl;
}