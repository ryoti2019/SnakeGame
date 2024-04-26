#include <DxLib.h>
#include "WinnerMes.h"
#include "../../../_debug/_DebugConOut.h"

WinnerMes::WinnerMes()
{
}

WinnerMes::~WinnerMes()
{
}

bool WinnerMes::Init(int winner)
{
	if(LoadDivGraph(
		"./Resource/image/win.png",
		static_cast<int>(CharID::MAX),
		1, static_cast<int>(CharID::MAX),
		338, 459 / static_cast<int>(CharID::MAX),
		& imageHdl[0])==-1)
	{
		TRACE("win.pngÇÃì«Ç›çûÇ›é∏îs\n");
		return false;
	}
	winnerID_ = winner;
	return true;
}

bool WinnerMes::Update(void)
{
	return false;
}

bool WinnerMes::Release(void)
{
	for (int no = 0; no < static_cast<int>(CharID::MAX); no++)
	{
		DeleteGraph(imageHdl[no]);
	}
	return true;
}

void WinnerMes::Draw(void)
{
	//DrawFormatString(0, 120, GetColor(255, 255, 255) , "%d", winnerID_);
	DrawGraph((800 - 338) / 2, 0, imageHdl[winnerID_], true);
}
