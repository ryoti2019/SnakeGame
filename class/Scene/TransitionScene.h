#pragma once
#include "ScnID.h"

class SceneMng;

class TransitionScene
{
public:
	TransitionScene();
	~TransitionScene();
	bool Init(TransitionType transitionType, ScnID scnID1, ScnID scnID2, SceneMng* sceneMng);
	NextScnID Update(char*keyData, char* keyDataOld);
	bool Release(void);
	void Draw(void);
	void TransitionDraw(void);
private:
	TransitionType transitionType_;
	ScnID scnID1_;
	ScnID scnID2_;
	SceneMng* sceneMng_;
	int count_;
	int screenID_;
};

