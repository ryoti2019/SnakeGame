#include <DxLib.h>
#include "ResultScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

ResultScene::ResultScene()
{
	TRACE("ResultSceneのコンストラクターの呼び出し\n");
}

ResultScene::~ResultScene()
{
	TRACE("ResultSceneのデストラクターの呼び出し\n");
}

bool ResultScene::Init(Player::State p1state, Player::State p2state,CharID p1ID,CharID p2ID)
{
	TRACE("ResultSceneのInit()の呼び出し\n");

	screenID_ = MakeScreen(800, 600, true);
	bgScreenID_ = MakeScreen(800, 600, true);

	GetDrawScreenGraph(0, 0, 800, 600, bgScreenID_);
	int winnerID = 0;
	if (p1state == Player::State::ALIVE)
	{
		winnerID = static_cast<int>(p1ID);
	}
	else if (p2state == Player::State::ALIVE)
	{
		winnerID = static_cast<int>(p2ID);
	}
	else
	{
		winnerID = static_cast<int>(CharID::DRAW);
	}
	winnerMes_.Init(winnerID);
	count_ = 0;
	ResultDraw();
	return true;
}

bool ResultScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	DeleteGraph(bgScreenID_);
	bgScreenID_ = 0;
	winnerMes_.Release();
	return true;
}

NextScnID ResultScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "ResultScene", 0);
	winnerMes_.Update();
	ResultDraw();
	if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	{
		return NextScnID{ ScnID::Title ,TransitionType::FadeInOut };
	}
	return NextScnID{ ScnID::Result,TransitionType::Non };
}

void ResultScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void ResultScene::ResultDraw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, bgScreenID_, true);
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawRectGraph(
		800 / 2 - count_, 600 / 2 - count_,
		800 / 2 - count_, 600 / 2 - count_,
		count_ * 2, count_ * 2,
		bgScreenID_, true
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	winnerMes_.Draw();
	count_ += 10;
}
