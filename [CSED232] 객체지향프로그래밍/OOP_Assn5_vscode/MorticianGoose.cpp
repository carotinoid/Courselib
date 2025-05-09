#include "MorticianGoose.h"
#include <iostream>
#include "BirdList.h"
#include "Macro.h"

// Constructor
MorticianGoose::MorticianGoose(std::string player_name) : Bird(player_name) {
	role = 4;
}

// Destructor
MorticianGoose::~MorticianGoose() {

}

// Skill function
void MorticianGoose::Skill(BirdList* bird_list) {
	std::string target_name = "", use_skill_input = "";

	std::cout << "염습를 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;

	// If the player doesn't want to use the skill, return
	if (use_skill_input == "N") return;

	bool allAlive = true;

	// Check if all bird is alive
	BirdNode* cur = bird_list->GetHead();
	while(cur != NULL) {
		if(!cur->GetBird()->IsAlive()) {
			allAlive = false;
		}
		cur = cur->GetNext();
	}
	if (allAlive) {
		// If all bird is alive, return
		std::cout << "염습 가능 대상이 없습니다." << std::endl;
		return;
	}
	std::cout << "염습하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> target_name;

	// Find target bird in bird_list.
	BirdNode* targetNode = bird_list->GetHead();
	while(targetNode != NULL) {
		if(targetNode->GetBird()->GetPlayerName() == target_name) {
			break;
		}
		targetNode = targetNode->GetNext();
	}
	Bird* target = targetNode->GetBird();
	if (targetNode == NULL) {
		std::cout << "ERR!" << std::endl;
		return;
	}
	// If target is alive, return
	if(target->IsAlive()) {
		// If target is alive, return
		std::cout << "염습 가능 대상이 아닙니다." << std::endl;
		return;
	}
	// If target is dead, print target's role
	std::cout << target_name << "의 역할은 " << BirdRoleName[target->GetRole()] << "입니다." << std::endl;
}
