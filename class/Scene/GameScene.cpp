#include <DxLib.h>
#include "GameScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

GameScene::GameScene()
{
	TRACE("GameSceneのコンストラクターの呼び出し\n");
}

GameScene::~GameScene()
{
	TRACE("GameSceneのデストラクターの呼び出し\n");
}

bool GameScene::Init(CharID player1, CharID player2)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("GameSceneのInit()の呼び出し\n");
	gameScreenID_ = MakeScreen(800, 512, true);

	charImage_[0].Init(player1);
	player_[0].Init(0, player1, 32, Player::State::ALIVE);
	player_[0].SetCharImage(&charImage_[0]);

	charImage_[1].Init(player2);
	player_[1].Init(1, player2, 32,Player::State::ALIVE);
	player_[1].SetCharImage(&charImage_[1]);

	bgImage_ = LoadGraph("Resource/image/bg.png");
	if (bgImage_ == -1)
	{
		TRACE("bg.pngの読み込み失敗\n");
		return false;
	}
	mapCtl_.Init();
	startMes_.Init();
	GameDraw();
	return true;
}

bool GameScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	DeleteGraph(gameScreenID_);
	gameScreenID_ = 0;

	for (int j = 0; j < PLAYER_MAX; j++)
	{
		charImage_[j].Release();
	}
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].Release();
	}
	DeleteGraph(bgImage_);
	bgImage_ = 0;

	mapCtl_.Release();
	startMes_.Release();
	return true;
}

NextScnID GameScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "GameScene", 0);
	if (!startMes_.Update())
	{
		for (int no = 0; no < PLAYER_MAX; no++)
		{
			player_[no].GetKeyState(keyData);
			player_[no].Update(&mapCtl_);
		}
		mapCtl_.Update();
	}
	GameDraw();
	if (player_[0].GetState() == Player::State::Dead ||
		player_[1].GetState() == Player::State::Dead)
	{
		return NextScnID{ ScnID::Result, TransitionType::Non };
	}
	return NextScnID{ ScnID::Game ,TransitionType::Non };
}

Player::State GameScene::GetPlayerState(int no)
{
	if (no >= PLAYER_MAX)
	{
		Player::State::Max;
	}
	return player_[no].GetState();
}

CharID GameScene::GetPlayerID(int no)
{
	if (no >= PLAYER_MAX)
	{
		Player::State::Max;
	}
	return player_[no].GetCharID();
}

void GameScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void GameScene::GameDraw(void)
{
	SetDrawScreen(gameScreenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, bgImage_, true);
	mapCtl_.Draw();
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].Draw();
	}

	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 64, gameScreenID_, true);
	startMes_.Draw();
}
