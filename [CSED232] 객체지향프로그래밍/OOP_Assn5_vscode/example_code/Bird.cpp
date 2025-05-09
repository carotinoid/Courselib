#include "Bird.h"
#include "BirdList.h"

#include <iostream>

Bird::Bird() {
}

Bird::~Bird() {

}

std::string Bird::GetPlayerName() const{
	return this->player_name;
}
