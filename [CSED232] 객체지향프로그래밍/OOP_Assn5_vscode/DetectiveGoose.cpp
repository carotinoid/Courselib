#include "DetectiveGoose.h"
#include <iostream>
#include "Macro.h"
#include "BirdList.h"

// Constructor
DetectiveGoose::DetectiveGoose(std::string player_name) : Bird(player_name) {
	role = 3;
}

// Destructor
DetectiveGoose::~DetectiveGoose() {

}

// Skill function
void DetectiveGoose::Skill(BirdList* bird_list) {
	std::string target_name = "", use_skill_input = "";
	std::cout << "조사를 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;
	// If the player doesn't want to use the skill, return
	if(use_skill_input == "N") return;
	std::cout << "조사하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> target_name;

	// Find the target player
	BirdNode* targetNode = bird_list->GetHead();
	while(targetNode != NULL) {
		if(targetNode->GetBird()->GetPlayerName() == target_name) {
			break;
		}
		targetNode = targetNode->GetNext();
	}
	Bird* target = targetNode->GetBird();

	// If the target player killed someone, print this message
	if(target->HasKilled())
		std::cout << target_name << "은(는) 이번 라운드에 누군가를 무참히 살해하였습니다..!" << std::endl;
	// If the target player didn't kill anyone, print this message
	else
		std::cout << target_name << "은(는) 이번 라운드에 아무도 해치지 않았습니다." << std::endl;
}
