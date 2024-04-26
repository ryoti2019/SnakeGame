#pragma once
#include "../../common/Vector2D.h"
#include "../CharImage.h"
#include "../MapCtl.h"

#define PLAYER_MAX 2

class Player
{
public:
	enum class State 
	{
		Non,		// �L�������I��
		ALIVE,		// �����i�I�𒆁j
		Dead,		// ���S
		Max			
	};
	Player();
	~Player();
	bool Init(int id, CharID charID, int chipSize, State state);
	bool Release(void);
	void Update(MapCtl* mapCtl);
	State GetState(void);
	bool SetState(State state);
	bool SetDir(void);
	void Draw(void);
	void SetCharImage(CharImage* charImage);
	const CharImage* GetCharImage(void);
	void GetKeyState(char* keyData);
	CharID GetCharID(void);
	Vector2D pos_;
	char keyNow_[static_cast<int>(Dir::Max)];
	char keyOld_[static_cast<int>(Dir::Max)];
private:
	Dir dir_;			// �v���C���[�̌���
	State state_;
	int keyList_[static_cast<int>(Dir::Max)];	// �������Ƃ̃L�[���X�g
	CharImage* charImage_;
	int chipSize_;
};

