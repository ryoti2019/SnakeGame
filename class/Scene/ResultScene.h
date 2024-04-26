#pragma once
#include "ScnID.h"
#include "./Unit/Player.h"
#include "./Unit/WinnerMes.h"
class ResultScene
{
public:
	ResultScene();
	~ResultScene();
	bool Init(Player::State p1state,Player::State p2state,CharID p1ID,CharID p2ID);
	bool Release(void);
	NextScnID Update(char* keyData, char* keyDataOld);
	void Draw(void);
	void ResultDraw(void);
private:
	WinnerMes winnerMes_;
	int count_;
	int screenID_;
	int bgScreenID_;
};

