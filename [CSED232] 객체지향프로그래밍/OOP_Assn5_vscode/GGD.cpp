#include <iostream>
#include <string>
#include "GGD.h"
#include "Macro.h"

#include "Goose.h" // Bird class
#include "Duck.h"
#include "Falcon.h"
#include "DodoBird.h"
#include "AssassinDuck.h"
#include "DetectiveGoose.h"
#include "MorticianGoose.h"

// Constructer, Dynamically allocate memory for bird_list, then set killMaxCount to 1 and round to 0.
GGD::GGD() {
	bird_list = new BirdList();
	killMaxCount = 1;
	round = 0;
}

// Destructor, delete bird_list.
GGD::~GGD() {
	delete bird_list;
}

// GameStart function, this function will be called when you start the program.
// In this function, you can add player, change killMaxCount, and start the game.
void GGD::GameStart() {
	// bird_list->ResetWin();
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
		case 1: // Add player
			AddPlayer();
			break;
		case 2: // Change killMaxCount
			ChangeKillMaxCount();
			break;
		case 3: // Start the game
			// Check if the game can be started
			if(!IsGameOver()) {
				std::cout << "게임 시작!!" << std::endl;
				BirdNode* current = bird_list->GetHead();
				while (current != NULL) {
					// Reset win count used from IsGameOver function
					current->GetBird()->ResetWin();
					current = current->GetNext();
				}
				BirdNode* cur = bird_list->GetHead();
				while (cur != NULL) {
					// Set killMaxCount to each Duck and AssassinDuck
					BirdRoleCode role = BirdRoleCode(cur->GetBird()->GetRole());
					if (role == BirdRoleCode::kDuck or role == BirdRoleCode::kAssassinDuck)
						cur->GetBird()->SetKillMaxCount(killMaxCount);
					cur = cur->GetNext();
				}
				return;
			}
			else {
				// If the game cannot be started, print the message
				std::cout << "게임을 시작할 수 없습니다!!" << std::endl;
			}
			break;
		default:
			break;
		}
	}
}

// This function adds player including making Bird and BirdNode instance.
void GGD::AddPlayer() {
	// Name and role_code are input from the user.
	std::string player_name;
	std::cout << "플레이어의 이름을 입력해주세요: ";
	std::cin >> player_name;
	int role_code;
	std::cout << "역할 번호를 입력해주세요: ";
	std::cin >> role_code;
	// Make Bird instance and BirdNode instance following the roles, then add it to bird_list.
	switch (BirdRoleCode(role_code)) {
	case BirdRoleCode::kFalcon: {
		Falcon* falcon = new Falcon(player_name);
		BirdNode* falcon_node = new BirdNode(falcon);
		bird_list->AddBirdNode(falcon_node);
		break;
	}
	case BirdRoleCode::kAssassinDuck: {
		AssassinDuck* assassin_duck = new AssassinDuck(player_name);
		BirdNode* assassin_duck_node = new BirdNode(assassin_duck);
		bird_list->AddBirdNode(assassin_duck_node);
		break;
	}
	case BirdRoleCode::kDuck: {
		Duck* duck = new Duck(player_name);
		BirdNode* duck_node = new BirdNode(duck);
		bird_list->AddBirdNode(duck_node);
		break;
	}
	case BirdRoleCode::kDetectiveGoose: {
		DetectiveGoose* detective_goose = new DetectiveGoose(player_name);
		BirdNode* detective_goose_node = new BirdNode(detective_goose);
		bird_list->AddBirdNode(detective_goose_node);
		break;
	}
	case BirdRoleCode::kMorticianGoose: {
		MorticianGoose* mortician_goose = new MorticianGoose(player_name);
		BirdNode* mortician_goose_node = new BirdNode(mortician_goose);
		bird_list->AddBirdNode(mortician_goose_node);
		break;
	}
	case BirdRoleCode::kGoose: {
		Goose* goose = new Goose(player_name);
		BirdNode* goose_node = new BirdNode(goose);
		bird_list->AddBirdNode(goose_node);
		break;
	}
	case BirdRoleCode::kDodoBird: {
		Dodo* dodo = new Dodo(player_name);
		BirdNode* dodo_node = new BirdNode(dodo);
		bird_list->AddBirdNode(dodo_node);
		break;
	}
	default:
		break;
	}
}

// This function changes killMaxCount.
void GGD::ChangeKillMaxCount() {
	int killMaxCount;
	std::cout << "값을 입력하세요: ";
	std::cin >> killMaxCount;
	// killMaxCount variable in this class is temporary.
	// When you start the game, the killMaxCount of Duck and AssassinDuck will be set to this value in GameStart() function.
	this->killMaxCount = killMaxCount;
}

// This function is called when the game is started.
// Moreover, this function will be called repeatedly until the game is over.
// This function is consist of two phases: Ability(Skill) Phase and Vote Phase.
// In the Ability(Skill) Phase, each bird uses its skill following the role.
// In the Vote Phase, each bird votes for the player to be killed.
void GGD::RoundProgress() {
	// Reset win count used from IsGameOver function
	BirdNode* killReset = bird_list->GetHead();
	while (killReset != NULL) {
		killReset->GetBird()->ResetKill();
		killReset = killReset->GetNext();
	}
	round++;
	// Print Rounds.
	std::cout << "----------------Round " << round << "----------------" << std::endl;
	//----------------Ability(Skill) Phase------------------
	for(int i = 0; i < 7; i ++) {
		BirdNode* cur = bird_list->GetHead();
		while(cur != NULL) {
			// If Bird is alive, it can use its skill.
			// Skill() member functions are implemented by pure virtual function.
			if(cur->GetBird()->IsAlive() and BirdRoleCode(cur->GetBird()->GetRole()) == BirdRoleCode(i)) {
				std::cout << cur->GetBird()->GetPlayerName() << "님 당신은 " << BirdRoleName[cur->GetBird()->GetRole()] << "입니다."<< std::endl;
				cur->GetBird()->Skill(bird_list);
			}
			cur = cur->GetNext();
		}
	}
	//----------------Vote Phase------------------
	int invalidVote = 0; // invalidVote is the number of responses "N".
	int* voted = new int[10000];
	for (int i = 0; i < 10000; i++) voted[i] = 0;
	std::string vote;
	BirdNode* cur = bird_list->GetHead();
	while(cur != NULL) {
		// If Bird is dead, it cannot vote.
		if(!cur->GetBird()->IsAlive()) {
			cur = cur->GetNext();
			continue;
		}
		// Falcon cannot vote.
		if(BirdRoleCode(cur->GetBird()->GetRole()) == BirdRoleCode::kFalcon) {
			std::cout << cur->GetBird()->GetPlayerName() << "님은 송골매이므로 무효표에 자동 투표됩니다." << std::endl;
			invalidVote++;
			cur = cur->GetNext();
			continue;
		}
		std::string vote_target, want;
		std::cout << cur->GetBird()->GetPlayerName() << "님 투표를 하시겠습니까? [Y/N]: ";
		std::cin >> want;
		// If the response is "N", it is invalid vote.
		if(want == "N") {
			invalidVote++;
			cur = cur->GetNext();
			continue;
		}
		// If the response is "Y", the player can vote.
		std::cout << "투표하고 싶은 플레이어의 이름을 입력하세요: ";
		std::cin >> vote_target;
		int cnt = 0;
		BirdNode* curr = bird_list->GetHead();
		while(curr != NULL) {
			if(curr->GetBird()->GetPlayerName() == vote_target) {
				voted[cnt]++;
				break;
			}
			curr = curr->GetNext();
			cnt++;
		}
		cur = cur->GetNext();
		continue;
	}

	// Num is the number of players.
	int num = 0;
	BirdNode* findingNumber = bird_list->GetHead();
	while(findingNumber != NULL) {
		num++;
		findingNumber = findingNumber->GetNext();
	}

	// Find the player who has the most votes.
	// Variable maxv is the number of votes of the player who has the most votes.
	// idx is the index of the player who has the most votes.
	// if idx is -1, no player is selected. (invalid vote)
	int maxv = invalidVote;
	int idx = -1;

	for (int i = 0; i < num; i++) {
		// Now is invalid but new most-voted player is appeared. New idx and updated maxv.
		if (idx == -1 and voted[i] > maxv) {
			maxv = voted[i];
			idx = i;
		// Now is not invalid, and new most-voted player is appeared, so idx and max must be updated.
		} else if(idx != -1 and voted[i] > maxv) {
			maxv = voted[i];
			idx = i;
		}
		// Now is not invalid, but the player who has the votes which is same as maxv is appeared. So idx is set to -1. (invalid vote)
		else if (idx != -1 and voted[i] == maxv) {
			idx = -1;
		}
	}

	// Print the result of the vote.
	// If idx is -1, no player is selected. (invalid vote)
	if(idx == -1) {
		std::cout << "전체 메시지: 이번 투표에서는 아무 조류도 당첨되지 않았습니다." << std::endl;
	} else {
		// If it is not invalid vote, idx is the index of the player who has the most votes.
		// Kill the player who has the most votes, and print the result.
		BirdNode* voted = bird_list->GetHead();
		for (int i = 0; i < idx; i++) {
			voted = voted->GetNext();
		}
		std::cout << "전체 메시지: " << voted->GetBird()->GetPlayerName() << "은(는) 더 좋은 곳을 갔습니다." << std::endl;
		voted->GetBird()->die();
		if (BirdRoleCode(voted->GetBird()->GetRole()) == BirdRoleCode::kDodoBird) voted->GetBird()->Win();
		if (BirdRoleCode(voted->GetBird()->GetRole()) == BirdRoleCode::kDuck
			or BirdRoleCode(voted->GetBird()->GetRole()) == BirdRoleCode::kAssassinDuck) {
			std::cout << "전체 메시지: " << voted->GetBird()->GetPlayerName() << "은(는) 오리입니다!!" << std::endl;
		}
		else std::cout << "전체 메시지: 맙소사 " << voted->GetBird()->GetPlayerName() << "은(는) 오리가 아닙니다!!" << std::endl;
	}
	delete[] voted;
}

// This function checks if the game is over.
// Find the number of each role, and check if the game is over.
// This function only checks if duck, goose, and falcon can be win.
// The judgement of dodo is in Vote Phase. it can be possible because dodo's win condition is not initialized when reset.
bool GGD::IsGameOver() {
	// If there is no player, the game is over (cannot start).
	if(bird_list->GetHead() == NULL) return true;

	BirdNode* reset = bird_list->GetHead();
	while(reset != NULL) {
		if (BirdRoleCode(reset->GetBird()->GetRole()) == BirdRoleCode::kDodoBird) {
			reset = reset->GetNext();
			continue;
		}
		reset->GetBird()->ResetWin();
		reset = reset->GetNext();
	}
	// Find the number of each role.
	int goose = 0;
	int duck = 0;
	int dodo = 0;
	int falcon = 0;
	// Find the first falcon, duck, and goose.
	// When the function PrintGameResult() is called, it judge with only the first falcon, duck, and goose.
	Bird* Falcon = NULL;
	BirdNode* fcur = bird_list->GetHead();
	while(fcur != NULL) {
		if(BirdRoleCode(fcur->GetBird()->GetRole()) == BirdRoleCode::kFalcon) {
			Falcon = fcur->GetBird();
			break;
		}
		fcur = fcur->GetNext();
	}
	Bird* Duck = NULL;
	BirdNode* dcur = bird_list->GetHead();
	while(dcur != NULL) {
		if(BirdRoleCode(dcur->GetBird()->GetRole()) == BirdRoleCode::kDuck
			or BirdRoleCode(dcur->GetBird()->GetRole()) == BirdRoleCode::kAssassinDuck) {
			Duck = dcur->GetBird();
			break;
		}
		dcur = dcur->GetNext();
	}
	Bird* Goose = NULL;
	BirdNode* gcur = bird_list->GetHead();
	while(gcur != NULL) {
		if(BirdRoleCode(gcur->GetBird()->GetRole()) == BirdRoleCode::kDetectiveGoose
			or BirdRoleCode(gcur->GetBird()->GetRole()) == BirdRoleCode::kMorticianGoose
			or BirdRoleCode(gcur->GetBird()->GetRole()) == BirdRoleCode::kGoose) {
			Goose = gcur->GetBird();
			break;
		}
		gcur = gcur->GetNext();
	}

	// Count the number of each role.
	BirdNode* cur = bird_list->GetHead();
	while(cur != NULL) {
		if(!cur->GetBird()->IsAlive()) {
			cur = cur->GetNext();
			continue;
		}
		switch (BirdRoleCode(cur->GetBird()->GetRole())) {
			case BirdRoleCode::kFalcon:
				// Falcon = (Falcon == NULL? cur->GetBird() : Falcon);
				falcon++;
				break;
			case BirdRoleCode::kAssassinDuck:
				// Duck = (Duck == NULL? cur->GetBird() : Duck);
				duck++;
				break;
			case BirdRoleCode::kDuck:
				// Duck = (Duck == NULL? cur->GetBird() : Duck);
				duck++;
				break;
			case BirdRoleCode::kDetectiveGoose:
				// Goose = (Goose == NULL? cur->GetBird() : Goose);
				goose++;
				break;
			case BirdRoleCode::kMorticianGoose:
				// Goose = (Goose == NULL? cur->GetBird() : Goose);
				goose++;
				break;
			case BirdRoleCode::kGoose:
				// Goose = (Goose == NULL? cur->GetBird() : Goose);
				goose++;
				break;
			case BirdRoleCode::kDodoBird:
				dodo++;
				break;
		}
		cur = cur->GetNext();
	}

	// With found the number of each role, check if the game is over.
	// Also check what role is the winner.
	if(falcon == 1 && duck + goose + dodo <= 1){
		Falcon->Win();
		return true;
	}
	if(duck >= goose + dodo + falcon){
		Duck->Win();
		return true;
	}
	if(duck == 0 and falcon == 0){
		Goose->Win();
		return true;
	}
	return false;
}

// Print the result of the game.
void GGD::PrintGameResult() {
	Bird* winner = NULL;
	BirdNode* cur = bird_list->GetHead();
	while(cur != NULL) {
		if(cur->GetBird()->HasWon()) {
			// In vote Phase, if Dodo is winner, Dodo->win is set to true.
			// The criteria of Dodo's win is special, so it is not reset.
			// If Dodo is winner, Falcon, Goose, Duck are must be losers.
			if(BirdRoleCode(cur->GetBird()->GetRole()) == BirdRoleCode::kDodoBird) {
				winner = cur->GetBird();
				break;
			}
			// If Dodo is not winner, the winner is the one among Falcon, Duck, and Goose checked in IsGameOver function.
			winner = (winner == NULL? cur->GetBird() : winner);
		}
		cur = cur->GetNext();
	}
	// If the winner is NULL, print "ERR!" and exit.
	// If all inputs are correct, this ERR message will not be printed.
	if (winner == NULL) { std::cout << "ERR!" << std::endl; exit(-1); }

	// Print the result of the game.
	switch(BirdRoleCode(winner->GetRole())) {
		case BirdRoleCode::kFalcon:
			std::cout << "전체 메시지: 송골매의 승리입니다!" << std::endl;
			break;
		case BirdRoleCode::kAssassinDuck:
		case BirdRoleCode::kDuck:
			std::cout << "전체 메시지: 오리의 승리입니다!" << std::endl;
			break;
		case BirdRoleCode::kDetectiveGoose:
		case BirdRoleCode::kMorticianGoose:
		case BirdRoleCode::kGoose:
			std::cout << "전체 메시지: 거위의 승리입니다!" << std::endl;
			break;
		case BirdRoleCode::kDodoBird:
			std::cout << "전체 메시지: 도도새의 승리입니다!" << std::endl;
			break;
		default:
			break;
	}

	// Exit the program.
	exit(0);
}

