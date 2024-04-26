#include <DxLib.h>
#include "SceneMng.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

SceneMng::SceneMng()
{
	TRACE("SceneMngの生成\n");
	Init();
}

SceneMng::~SceneMng()
{
	TRACE("SceneMngの破棄\n");
	Release();
}

void SceneMng::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		if (nextScnID_.id != scnID_)
		{
			scnID_ = SetupScene(nextScnID_);
		}
		Update();
		Draw();
	}
}

void SceneMng::DrawScene(ScnID scnID)
{
	switch (scnID)
	{
	case ScnID::Logo:
		logoScene.Draw();
		break;
	case ScnID::Title:
		titleScene.Draw();
		break;
	case ScnID::Select:
		selectScene.Draw();
		break;
	case ScnID::Game:
		gameScene.Draw();
		break;
	case ScnID::Result:
		resultScene.Draw();
		break;
	case ScnID::Transition:
		transitionScene.Draw();
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID_);
		break;
	}
}

bool SceneMng::Init(void)
{
	if (SysInit() == false)
	{
		return false;
	}
	scnID_ = ScnID::Non;
	nextScnID_ = { ScnID::Logo,TransitionType::FadeIn };
	//titleScene.Init();
	return true;
}

bool SceneMng::Release(void)
{
	TRACE("SceneMngのRelease()の呼び出し\n");
	DxLib_End();
	return true;
}

void SceneMng::Update(void)
{
	//for (int j = 0; j < 256; j++)
	//{
	//	keyBufOld_[j] = keyBuf_[j];
	//}
	memcpy(&keyBufOld_[0], &keyBuf_[0],sizeof(keyBufOld_));


	GetHitKeyStateAll(&keyBuf_[0]);

	switch (scnID_)
	{
	case ScnID::Logo:
		nextScnID_ = logoScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Title:
		nextScnID_ = titleScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Select:
		nextScnID_ = selectScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Game:
		nextScnID_ = gameScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Result:
		nextScnID_ = resultScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Transition:
		nextScnID_ = transitionScene.Update(&keyBuf_[0], &keyBufOld_[0]);
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID_);
		break;
	}
	//titleScene.Update();
	//gameScene.Update();
	//selectScene.Update();
	//resultScene.Update();
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	switch (scnID_)
	{
	case ScnID::Logo:
		logoScene.Draw();
		break;
	case ScnID::Title:
		titleScene.Draw();
		break;
	case ScnID::Select:
		selectScene.Draw();
		break;
	case ScnID::Game:
		gameScene.Draw();
		break;
	case ScnID::Result:
		resultScene.Draw();
		break;
	case ScnID::Transition:
		transitionScene.Draw();
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID_);
		break;
	}
	_dbgDraw();
	ScreenFlip();
}

bool SceneMng::SysInit(void)
{
	TRACE("SysInitの呼び出し\n");
	SetWindowText("2216008_寺師 遼");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	srand((unsigned int)time(NULL));
	return true;
}

ScnID SceneMng::SetupScene(NextScnID nextID)
{
	ReleaseScene(scnID_);
	if (scnID_ == ScnID::Transition)
	{
		return nextID.id;
	}
	if (nextID.transitionType != TransitionType::Non)
	{
		transitionScene.Init(nextID.transitionType, scnID_,nextScnID_.id, this);
		return ScnID::Transition;
	}
	else
	{
		switch (nextID.id)
		{
		case ScnID::Logo:
			logoScene.Init();
			break;
		case ScnID::Title:
			titleScene.Init();
			break;
		case ScnID::Select:
			selectScene.Init();
			break;
		case ScnID::Game:
			gameScene.Init(selectScene.GetSelPlayer(0), selectScene.GetSelPlayer(1));
			break;
		case ScnID::Result:
			resultScene.Init(gameScene.GetPlayerState(0), gameScene.GetPlayerState(1), gameScene.GetPlayerID(0), gameScene.GetPlayerID(1));
			break;
		case ScnID::Transition:
			TRACE("移行IDで使わないScnID:%d\n", nextID);
			break;
		case ScnID::Non:
			// 何もしない
			break;
		default:
			TRACE("未知のScnID:%d\n", nextID);
			break;
		}
	}
	return nextID.id;
}

bool SceneMng::ReleaseScene(ScnID scnID)
{
	if (nextScnID_.transitionType != TransitionType::Non)
	{
		// 次のシーンがトランジションの場合、描画に使うので開放しない
		return false;
	}
	switch (scnID)
	{
	case ScnID::Logo:
		logoScene.Release();
		break;
	case ScnID::Title:
		titleScene.Release();
		break;
	case ScnID::Select:
		selectScene.Release();
		break;
	case ScnID::Game:
		gameScene.Release();
		break;
	case ScnID::Result:
		resultScene.Release();
		break;
	case ScnID::Transition:
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID);
		break;
	}
	return true;
}
