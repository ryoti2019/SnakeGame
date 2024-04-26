#include <DxLib.h>
#include "LogoScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

LogoScene::LogoScene()
{
	TRACE("LogoScene�̃R���X�g���N�^�[�̌Ăяo��\n");
}

LogoScene::~LogoScene()
{
	TRACE("LogoScene�̃f�X�g���N�^�[�̌Ăяo��\n");
}

bool LogoScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("LogoScene��Init()�̌Ăяo��\n");
	logoImage_ = LoadGraph("./Resource/image/logo.png");
	if (logoImage_ == -1)
	{
		TRACE("logo.png�̓ǂݍ��ݎ��s\n");
		return false;
	}
	count = 0;
	LogoDraw();
	return true;
}

bool LogoScene::Release(void)
{
	TRACE("LogoScene��Release()�̌Ăяo��\n");
	DeleteGraph(screenID_);
	DeleteGraph(logoImage_);
	screenID_ = 0;
	logoImage_ = 0;
	return true;
	return false;
}

NextScnID LogoScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "LogoScene", 0);
	LogoDraw();
	if (count > 60 * 2 || keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	{
		return NextScnID{ ScnID::Title ,TransitionType::FadeInOut };
	}
	count++;
	return NextScnID{ ScnID::Logo,TransitionType::Non };
}

void LogoScene::LogoDraw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph((800 - 646) / 2, (600 - 84) / 2, logoImage_, true);
}

void LogoScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}
