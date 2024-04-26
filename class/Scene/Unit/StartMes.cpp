#include <DxLib.h>
#include "StartMes.h"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

constexpr int imageSizeX = 300;
constexpr int imageSizeY = 255 / 2;

StartMes::StartMes()
{
}

StartMes::~StartMes()
{
}

bool StartMes::Init(void)
{
	if (LoadDivGraph("./Resource/image/start_mes.png",
		static_cast<int>(Mes::Max),
		1,
		static_cast<int>(Mes::Max),
		imageSizeX,
		imageSizeY,
		&imageHdl[0]) == -1)
	{
		TRACE("スタート用画像の読み込み失敗\n");
		return false;
	}
	count = 0;
	return true;
}

bool StartMes::Update(void)
{
	if (count>240)
	{
		return false;
	}
	count++;
	return true;
}

bool StartMes::Release(void)
{
	for (int j = 0; j < static_cast<int>(Mes::Max); j++)
	{
		DeleteGraph(imageHdl[j]);
	}
	return true;
}

void StartMes::Draw(void)
{
	if (count >= 240)
	{
		return;
	}
	if (count < 180)
	{
		// imageHdl[0]
		DrawGraph(
			(800 - imageSizeX) / 2,
			(600 - imageSizeY) / 2,
			imageHdl[0],
			true);
	}
	else
	{
		// imageHdl[1]
		DrawGraph(
			(800 - imageSizeX) / 2,
			(600 - imageSizeY) / 2,
			imageHdl[1],
			true);
	}
}
