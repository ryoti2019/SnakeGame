#pragma once
#include "Map.h"
#include "../common/Vector2D.h"
#define BLOCK_PTN_MAX (7)
#define BLOCK_CNT_INV (3)
#define BLOCK_MAX_SIZE_CNT ((BLOCK_PTN_MAX - 1) * BLOCK_CNT_INV)

class MapCtl
{
public:
	MapCtl();
	~MapCtl();
	void Update(void);
	void Draw(void);
	bool Init(void);
	bool Release(void);
	int SetBlock(Vector2D pos, int num);
	int GetBlock(Vector2D pos);
	bool isOnBlock(Vector2D pos);
	int mapData_[MAP_CHIP_COUNT_Y][MAP_CHIP_COUNT_X];
	int blockImage_[BLOCK_PTN_MAX];
};

