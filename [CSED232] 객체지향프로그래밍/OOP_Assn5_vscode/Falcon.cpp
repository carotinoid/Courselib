#include "Falcon.h"
#include <iostream>
#include "Macro.h"
#include "BirdList.h"

// Constructor
Falcon::Falcon(std::string player_name) : Bird(player_name) {
	role = 0;
}

// Destructor
Falcon::~Falcon() {

}

void Falcon::Skill(BirdList* bird_list) {
	std::string target_name = "", use_skill_input = "";
	std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;
	// If the player doesn't want to use the skill, return
	if(use_skill_input == "N") return;
	std::cout << "살해하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> target_name;
	std::cout << "전체 메시지: " << target_name << "이(가) 무참히 살해당하였습니다.." << std::endl;

	// Find target bird in bird_list, then kill.
	BirdNode* target = bird_list->GetHead();
	while(target != NULL) {
		if(target->GetBird()->GetPlayerName() == target_name) {
			break;
		}
		target = target->GetNext();
	}
	// 이름을 틀리게 입력하는 경우는 없다고 가정하므로, target은 nullptr이 아님.
	target->GetBird()->die();
}

