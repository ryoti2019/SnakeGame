#include <DxLib.h>
#include "SelectScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

SelectScene::SelectScene()
{
	TRACE("SelectSceneのコンストラクターの呼び出し\n");
}

SelectScene::~SelectScene()
{
	TRACE("SelectSceneのデストラクターの呼び出し\n");
}

bool SelectScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	gameScreenID_ = MakeScreen(800, 512, true);
	TRACE("SelectSceneのInit()の呼び出し\n");
	for (int j = 0; j < static_cast<int>(CharID::MAX); j++)
	{
		charImage_[j].Init(static_cast<CharID>(j));
	}
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].Init(no, static_cast<CharID>(no), 32, Player::State::Non);
		player_[no].pos_.y += 32;
		player_[no].SetCharImage(&charImage_[no]);
	}

	bgImage_ = LoadGraph("Resource/image/bg.png");
	if (bgImage_ == -1)
	{
		TRACE("bg.pngの読み込み失敗\n");
		return false;
	}
	logoImage_ = LoadGraph("Resource/image/char_sel.png");
	if (logoImage_ == -1)
	{
		TRACE("char_sel.pngの読み込み失敗\n");
		return false;
	}
	SelectDraw();
	return true;
}

bool SelectScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	DeleteGraph(gameScreenID_);
	gameScreenID_ = 0;

	for (int j = 0; j < static_cast<int>(CharID::MAX); j++)
	{
		charImage_[j].Release();
	}
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].Release();
	}
	DeleteGraph(bgImage_);
	bgImage_ = 0;
	DeleteGraph(logoImage_);
	logoImage_ = 0;

	return true;
}

NextScnID SelectScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "SelectScene", 0);
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].GetKeyState(keyData);

		if (player_[no].keyNow_[static_cast<int>(Dir::Left)] &&
			!player_[no].keyOld_[static_cast<int>(Dir::Left)])
		{
			int id = static_cast<int>(player_[no].GetCharImage()->GetID()) - 1;
			if (id < 0)
			{
				id = static_cast<int>(CharID::WAR);
			}
			player_[no].SetCharImage(&charImage_[id]);
		}
		if (player_[no].keyNow_[static_cast<int>(Dir::Right)] &&
			!player_[no].keyOld_[static_cast<int>(Dir::Right)])
		{
			int id = static_cast<int>(player_[no].GetCharImage()->GetID()) + 1;
			if (id > static_cast<int>(CharID::WAR))
			{
				id = static_cast<int>(CharID::BOY);
			}
			player_[no].SetCharImage(&charImage_[id]);
		}
		// 決定処理
		if (player_[no].GetState() == Player::State::Non)
		{
			if (player_[no].keyNow_[static_cast<int>(Dir::Up)] &&
				!player_[no].keyOld_[static_cast<int>(Dir::Up)])
			{
				player_[no].SetState(Player::State::ALIVE);
				player_[no].pos_.y -= 32;
			}
		}
		// キャンセル処理
		if (player_[no].GetState() == Player::State::ALIVE)
		{
			if (player_[no].keyNow_[static_cast<int>(Dir::Down)] &&
				!player_[no].keyOld_[static_cast<int>(Dir::Down)])
			{
				player_[no].SetState(Player::State::Non);
				player_[no].pos_.y += 32;
			}
		}
	}
	SelectDraw();
	//bool flag = true;
	//for (int no = 0; no < PLAYER_MAX; no++)
	//{
	//	if (player_[no].GetState() == !Player::State::ALIVE)
	//	{
	//		return ScnID::Select;
	//	}
	// return ScnID::Game;
	//}

	if (player_[0].GetState() == Player::State::ALIVE &&
		player_[1].GetState() == Player::State::ALIVE)
	{
		return NextScnID{ ScnID::Game, TransitionType::Non };
	}

	return NextScnID{ ScnID::Select,TransitionType::Non };
}

void SelectScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
	DrawGraph(109, 0, logoImage_, true);
	
}

void SelectScene::SelectDraw(void)
{
	SetDrawScreen(gameScreenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, bgImage_, true);
	for (int no = 0; no < PLAYER_MAX; no++)
	{
		player_[no].Draw();
	}

	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 64, gameScreenID_, true);
}

CharID SelectScene::GetSelPlayer(int no)
{
	return player_[no].GetCharID();
}
