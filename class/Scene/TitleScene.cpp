#include <DxLib.h>
#include "TitleScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

TitleScene::TitleScene()
{
	TRACE("TitleScene�̃R���X�g���N�^�[�̌Ăяo��\n");
	//Init();
}

TitleScene::~TitleScene()
{
	TRACE("TitleScene�̃f�X�g���N�^�[�̌Ăяo��\n");
}

bool TitleScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("TitleScene��Init()�̌Ăяo��\n");
	titleImage_ = LoadGraph("./Resource/image/title.png");
	if (titleImage_ == -1)
	{
		TRACE("title.png�̓ǂݍ��ݎ��s\n");
		return false;
	}
	count = 0;
	TitleDraw();
	return true;
}

bool TitleScene::Release(void)
{
	TRACE("TitleScene��Release()�̌Ăяo��\n");
	DeleteGraph(screenID_);
	DeleteGraph(titleImage_);
	screenID_ = 0;
	titleImage_ = 0;
	return true;
}

NextScnID TitleScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "TitleScene", 0);
	//TRACE("TitleScene��Update()�̌Ăяo��\n");
	TitleDraw();
	if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	{
		return NextScnID{ ScnID::Select ,TransitionType::FadeInOut };
	}
	return NextScnID{ ScnID::Title,TransitionType::Non };
}

void TitleScene::Draw(void)
{
	//TRACE("TitleScene��Draw()�̌Ăяo��\n");
	DrawGraph(0, 0, screenID_, true);
}

void TitleScene::TitleDraw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, titleImage_, true);

	if (!((count / 40) % 2))
	{

		int mesSizeX = GetDrawStringWidth("�o�t�r�g�@�r�o�`�b�d�@�j�d�x", 14);

		DrawString(((680 - mesSizeX) / 2) - 1, (600 * 2 / 3) - 1, "�o�t�r�g�@�r�o�`�b�d�@�j�d�x", 0xffffff);
		DrawString((680 - mesSizeX) / 2, 600 * 2 / 3, "�o�t�r�g�@�r�o�`�b�d�@�j�d�x", 0x0000ff);
	}
	count++;

}
