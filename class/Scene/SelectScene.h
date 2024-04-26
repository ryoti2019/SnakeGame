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
	int bgImage_;		// �w�i
	int logoImage_;		// �L�����̑I�����S
	CharImage charImage_[static_cast<int>(CharID::MAX)];
	Player player_[PLAYER_MAX];

	// �X�N���[��
	int screenID_;
	int gameScreenID_;
};

