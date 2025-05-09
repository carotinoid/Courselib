#include <iostream>
#include <string>
#include "GGD.h"
#include "Macro.h"

GGD::GGD() {

}
GGD::~GGD() {

}
void GGD::GameStart() {
	int select;
	bool game_start = false;
	while (!game_start) {
		std::cout << "------------게임 설정 메뉴-------------\n";
		std::cout << "1. 플레이어 추가\n";
		std::cout << "2. 라운드당 오리 진영 살조 제한 횟수 설정\n";
		std::cout << "3. 게임 시작하기!\n";
		std::cout << "---------------------------------------\n";
		std::cout << "메뉴 번호를 입력하세요: ";
		std::cin >> select;

		switch (select)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}
void GGD::RoundProgress() {

}

bool GGD::IsGameOver() {
	bool res = true;
	return res;
}

void GGD::PrintGameResult() {

}

void GGD::AddPlayer() {
	std::string player_name;
	std::cout << "플레이어의 이름을 입력해주세요: ";
	std::cin >> player_name;
	
	int role_code;
	std::cout << "역할 번호를 입력해주세요: ";
	std::cin >> role_code;

	switch (BirdRoleCode(role_code)) {
	case BirdRoleCode::kFalcon:
		break;
	case BirdRoleCode::kAssassinDuck:
		break;
	case BirdRoleCode::kDuck:
		break;
	case BirdRoleCode::kDetectiveGoose:
		break;
	case BirdRoleCode::kMorticianGoose:
		break;
	case BirdRoleCode::kGoose:
		break;
	case BirdRoleCode::kDodoBird:
		break;
	default:
		break;
	}
}
