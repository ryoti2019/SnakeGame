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
		Non,		// キャラ未選択
		ALIVE,		// 生存（選択中）
		Dead,		// 死亡
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
	Dir dir_;			// プレイヤーの向き
	State state_;
	int keyList_[static_cast<int>(Dir::Max)];	// 方向ごとのキーリスト
	CharImage* charImage_;
	int chipSize_;
};

