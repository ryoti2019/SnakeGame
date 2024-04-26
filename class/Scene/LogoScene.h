#pragma once
#include "ScnID.h"

class LogoScene
{
public:
	LogoScene();
	~LogoScene();
	bool Init(void);
	bool Release(void);
	NextScnID Update(char* keyData, char* keyDataOld);
	void LogoDraw(void);
	void Draw(void);
private:
	int logoImage_;
	int screenID_;
	int count;
};

