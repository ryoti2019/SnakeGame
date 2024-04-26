#pragma once
#include "CharImage.h"
#include "Unit/Player.h"
#include "ScnID.h"

class SelectScene
{
public:
	SelectScene();
	~SelectScene();
	bool Init(void);
	bool Release(void);
	NextScnID Update(char* keyData, char* keyDataOld);
	void Draw(void);
	void SelectDraw(void);
	CharID GetSelPlayer(int no);
private:
	int bgImage_;		// 背景
	int logoImage_;		// キャラの選択ロゴ
	CharImage charImage_[static_cast<int>(CharID::MAX)];
	Player player_[PLAYER_MAX];

	// スクリーン
	int screenID_;
	int gameScreenID_;
};

