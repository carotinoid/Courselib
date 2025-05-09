#pragma once
#include "BirdList.h"
class GGD
{
private:
	BirdList* bird_list;
public:
	// Do not change any function declaration from here //
	GGD();
	~GGD();
	void GameStart();
	void RoundProgress();
	bool IsGameOver();
	void PrintGameResult();
	// Do not change any function declaration to here //

	void AddPlayer(); // You can change the function declaration
	void ChangeKillMaxCount(); // When you select 2 in menu, this function will be called.
	int killMaxCount;
	int round; //round
};

