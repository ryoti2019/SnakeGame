#pragma once
#include "Unit/CharID.h"

enum class Dir
{
	Down,
	Left,
	Right,
	Up,
	Max
};

#define ANIME_IMAGE_MAX 3	// アニメーション総数

class CharImage
{
public:
	CharImage();
	~CharImage();
	bool Init(CharID charID);
	bool Release(void);
	int chipImage_[static_cast<int>(Dir::Max)][ANIME_IMAGE_MAX];
	CharID GetID(void) const;
private:
	CharID charID_;
};

