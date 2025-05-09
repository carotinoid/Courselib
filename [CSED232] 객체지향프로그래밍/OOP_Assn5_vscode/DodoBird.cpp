#include "DodoBird.h"

#include <iostream>

// Constructor
Dodo::Dodo(std::string player_name) : Bird(player_name) {
	role = 6;
}

// Destructor
Dodo::~Dodo() {

}

// Skill function
// Dodo has no skill
void Dodo::Skill(BirdList* bird_list) {
	std::cout << "당신은 능력이 없는 조류입니다." << std::endl;
}
