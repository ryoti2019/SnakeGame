#include <DxLib.h>
#include "MapCtl.h"
#include "Unit/Player.h"
#include "../../_debug/_DebugConOut.h"

#define CHIP_SIZE (32)

MapCtl::MapCtl()
{
}

MapCtl::~MapCtl()
{
}

void MapCtl::Update(void)
{
	for (int y = 0; y < MAP_CHIP_COUNT_Y; y++)
	{
		for (int x = 0; x < MAP_CHIP_COUNT_X; x++)
		{
			if (mapData_[y][x] > 0 &&
				mapData_[y][x] < BLOCK_MAX_SIZE_CNT)
			{
				mapData_[y][x]++;
			}

		}
	}
	
}

void MapCtl::Draw(void)
{
	for (int y = 1; y < MAP_CHIP_COUNT_Y - 1; y++)
	{
		for (int x = 1; x < MAP_CHIP_COUNT_X - 1; x++)
		{
			if (mapData_[y][x] > 0)
			{
				int mapID = mapData_[y][x] / BLOCK_CNT_INV;
				mapID = mapID < BLOCK_PTN_MAX ? mapID : 0;
				DrawGraph(
					x * CHIP_SIZE,
					y * CHIP_SIZE,
					blockImage_[mapID],
					true
				);
			}
		}
	}
}

bool MapCtl::Init(void)
{
	if(LoadDivGraph(
		"Resource/image/block.png",
		BLOCK_PTN_MAX,
		BLOCK_PTN_MAX,
		1,
		CHIP_SIZE,
		CHIP_SIZE,
		blockImage_) == -1)
	{
	TRACE("ブロック画像の読み込み失敗");
	return false;
	}
	memset(mapData_, 0, sizeof(mapData_));
	for (int x = 0; x < MAP_CHIP_COUNT_X; x++)
	{
		mapData_[0][x] = BLOCK_MAX_SIZE_CNT;
		mapData_[MAP_CHIP_COUNT_Y - 1][x] = BLOCK_MAX_SIZE_CNT;
	}
	for (int y = 0; y < MAP_CHIP_COUNT_Y; y++)
	{
		mapData_[y][0] = BLOCK_MAX_SIZE_CNT;
		mapData_[y][MAP_CHIP_COUNT_X - 1] = BLOCK_MAX_SIZE_CNT;
	}
	return true;
}

bool MapCtl::Release(void)
{
	for (int no = 2; no < BLOCK_PTN_MAX; no++)
	{
		DeleteGraph(blockImage_[no]);
	}
	return true;
}

int MapCtl::SetBlock(Vector2D pos, int num)
{
	Vector2D chipPos;
	chipPos.x = pos.x / CHIP_SIZE;
	chipPos.y = pos.y / CHIP_SIZE;

	if (chipPos.x < 0 ||
		chipPos.x >= MAP_CHIP_COUNT_X ||
		chipPos.y < 0 ||
		chipPos.y >= MAP_CHIP_COUNT_Y)
	{
		// 範囲外の場合は0を返す
		return 0;
	}
	if (mapData_[chipPos.y][chipPos.x] == 0)
	{
		mapData_[chipPos.y][chipPos.x] = num;
	}
	

	return mapData_[chipPos.y][chipPos.x];
}

int MapCtl::GetBlock(Vector2D pos)
{
	Vector2D chipPos;
	chipPos.x = pos.x / CHIP_SIZE;
	chipPos.y = pos.y /CHIP_SIZE;

	if (chipPos.x < 0 ||
		chipPos.x >= MAP_CHIP_COUNT_X ||
		chipPos.y < 0 ||
		chipPos.y >= MAP_CHIP_COUNT_Y)
	{
		// 範囲外の場合は0を返す
		return 0;
	}
	return mapData_[chipPos.y][chipPos.x];
}

bool MapCtl::isOnBlock(Vector2D pos)
{
	//if (GetBlock(pos) >= BLOCK_MAX_SIZE_CNT)
	//{
	//	return true;
	//}
	//return false;
	return (GetBlock(pos) >= BLOCK_MAX_SIZE_CNT);
}
