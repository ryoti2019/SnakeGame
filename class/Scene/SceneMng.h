#pragma once
#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "ResultScene.h"
#include "TransitionScene.h"

#include "ScnID.h"

class SceneMng
{
public:
	SceneMng();
	~SceneMng();
	void Run(void);
	void DrawScene(ScnID scnID);
	ScnID SetupScene(NextScnID nextID);
	bool ReleaseScene(ScnID scnID);
private:
	bool Init(void);
	bool Release(void);
	void Update(void);
	void Draw(void);
	bool SysInit(void);

	ScnID scnID_;
	NextScnID nextScnID_;

	LogoScene logoScene;
	TitleScene titleScene;
	SelectScene selectScene;
	GameScene gameScene;
	ResultScene resultScene;
	TransitionScene transitionScene;

	char keyBuf_[256];
	char keyBufOld_[256];
};

