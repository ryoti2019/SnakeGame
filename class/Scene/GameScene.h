#pragma once
#include "ScnID.h"
#include "Unit/Player.h"
#include "MapCtl.h"
#include "./Unit/StartMes.h"


class GameScene
{
public:
	GameScene();
	~GameScene();
	bool Init(CharID player1,CharID player2);
	bool Release(void);
	NextScnID Update(char* keyData, char* keyDataOld);
	Player::State GetPlayerState(int no);
	CharID GetPlayerID(int no);
	void Draw(void);
	void GameDraw(void);
private:
	int bgImage_;
	CharImage charImage_[PLAYER_MAX];
	Player player_[PLAYER_MAX];
	MapCtl mapCtl_;
	StartMes startMes_;
	int screenID_;
	int gameScreenID_;
};

