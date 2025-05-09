#include "Duck.h"
#include <iostream>
#include "BirdList.h"
#include "Macro.h"

// Constructor
Duck::Duck(std::string player_name) : Bird(player_name) {
	role = 2;
}

// Destructor
Duck::~Duck() {

}

// Skill function
void Duck::Skill(BirdList* bird_list) {
	std::string target_name = "", use_skill_input = "";

	std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;
	// If the player doesn't want to use the skill, return
	if(use_skill_input == "N") return;
	// Find killCount in this round (by previous duck)
	int killCount = 0;
	BirdNode* cur = bird_list->GetHead();
	while(cur != NULL) {
		if(cur->GetBird()->HasKilled()
			and BirdRoleCode(cur->GetBird()->GetRole()) != BirdRoleCode::kFalcon) killCount++;
		cur = cur->GetNext();
	}

	// If killCount is bigger or equal than killMaxCount, return.
	if(killCount >= killMaxCount) {
		std::cout << "라운드당 오리 진영의 살조 제한 횟수에 도달하였습니다." << std::endl;
		return;
	}

	// Else, Duck can kill other.
	std::cout << "살해하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> target_name;
	this->kill = true;
	std::cout << "전체 메시지: " << target_name << "이(가) 무참히 살해당하였습니다.." << std::endl;

	// Find target bird in bird_list, then kill.
	BirdNode* targetNode = bird_list->GetHead();
	while(targetNode != NULL) {
		if(targetNode->GetBird()->GetPlayerName() == target_name) {
			break;
		}
		targetNode = targetNode->GetNext();
	}
	Bird* target = targetNode->GetBird();
	target->die();
}
