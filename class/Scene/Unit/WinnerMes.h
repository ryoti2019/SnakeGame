#pragma once
#include "CharID.h"
class WinnerMes
{
public:
	WinnerMes();
	~WinnerMes();
	bool Init(int winner);
	bool Update(void);
	bool Release(void);
	void Draw(void);
private:
	int winnerID_;
	int count;
	int imageHdl[static_cast<int>(CharID::MAX)];
};

