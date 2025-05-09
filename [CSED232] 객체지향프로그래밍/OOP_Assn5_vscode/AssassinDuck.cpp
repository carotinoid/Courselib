#include "AssassinDuck.h"
#include <iostream>
#include "Macro.h"
#include "BirdList.h"

// Constructor
AssassinDuck::AssassinDuck(std::string player_name) : Bird(player_name) {
	role = 1;
	assassinate_count = 0;
}

// Destructor
AssassinDuck::~AssassinDuck() {
}

// Skill function
void AssassinDuck::Skill(BirdList* bird_list) {
	std::string target_name = "", use_skill_input = "";
	//--------------------  assassinate  ------------------
	std::cout << "암살을 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;
	if(use_skill_input == "Y") {
		// If input is "Y" but already used assassinate skill 2 times, print message.
		if(assassinate_count >= AssassinateMaxCount) {
		std::cout << "더 이상 암살 능력을 사용할 수 없습니다!" << std::endl;
	} else {
		// Input target name and role.
		std::cout << "암살하고 싶은 플레이어의 이름을 입력하세요: ";
		std::cin >> target_name;
		int targetRole;
		std::cout << "암살하고 싶은 플레이어의 역할 번호를 입력하세요: ";
		std::cin >> targetRole;
		

		// Find target bird in bird_list.
		BirdNode* targetNode = bird_list->GetHead();
		while(targetNode != NULL) {
			if(targetNode->GetBird()->GetPlayerName() == target_name) {
				break;
			}
			targetNode = targetNode->GetNext();
		}

		// If target bird is not found, print error message.
		// If all input is correct, ERR message will not be printed.
		if (targetNode == NULL) std::cout << "ERR!" << std::endl;

		Bird* target = targetNode->GetBird();

		// If target bird's role and suggested role is same, kill target bird.
		if(target->GetRole() == targetRole) {
			std::cout << "전체 메시지: " << target_name << "이(가) 무참히 살해당하였습니다.." << std::endl;
			target->die();
			assassinate_count++;
		}
		// Else, Roles are different, print message and it will suicide.
		else {
			std::cout << "전체 메시지: " << this->player_name << "은(는) 극단적 선택을 하였습니다." << std::endl;
			this->die();
			return;
		}
	}
	}
	// After using skill:assassinate, then use this.
	//----------------------  Kill bird  ------------------------
	std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
	std::cin >> use_skill_input;
	// If the response is "N", return.
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
	// Find target bird in bird_list.
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