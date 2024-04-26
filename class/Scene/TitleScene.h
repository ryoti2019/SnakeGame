#pragma once
#include "ScnID.h"
class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	bool Init(void);
	bool Release(void);
	NextScnID Update(char* keyData, char* keyDataOld);
	void TitleDraw(void);
	void Draw(void);
private:
	int titleImage_;
	int screenID_;
	int count;
};

