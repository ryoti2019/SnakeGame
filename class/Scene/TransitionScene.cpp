#include <DxLib.h>
#include "TransitionScene.h"
#include "SceneMng.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

TransitionScene::TransitionScene()
{
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init(TransitionType transitionType, ScnID scnID1, ScnID scnID2, SceneMng* sceneMng)
{
	scnID1_ = scnID1;
	scnID2_ = scnID2;
	sceneMng_ = sceneMng;
	screenID_ = MakeScreen(800, 600, true);

	sceneMng_->SetupScene({ scnID2_, TransitionType::Non });
	transitionType_ = transitionType;
	count_ = 0;
	TransitionDraw();
	return true;
}

NextScnID TransitionScene::Update(char* keyData, char* keyDataOld)
{
	_TRACE_S(0x00ff00, "TransitionScene", 0);
	switch (transitionType_)
	{
	case TransitionType::FadeInOut:
		if (count_ > 100 + 255)
		{
			return { scnID2_, TransitionType::Non };
		}
		count_++;
		break;
	case TransitionType::FadeIn:
		if (count_ > 255)
		{
			return { scnID2_, TransitionType::Non };
		}
		count_++;
		break;
	default:
		TRACE("–¢’m‚ÌTransitionType:%d", static_cast<int>(transitionType_));
		break;
	}
	TransitionDraw();
	return { ScnID::Transition, TransitionType::Non };
}

bool TransitionScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	sceneMng_->ReleaseScene(scnID1_);
	return true;
}

void TransitionScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void TransitionScene::TransitionDraw(void)
{
	SetDrawScreen(screenID_);

	switch (transitionType_)
	{
	case TransitionType::FadeInOut:
			ClsDrawScreen();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_ < 255 ? 255 - count_ : 0);
			sceneMng_->DrawScene(scnID1_);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_ > 100 ? count_ - 100 : 0);
			sceneMng_->DrawScene(scnID2_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case TransitionType::FadeIn:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
			sceneMng_->DrawScene(scnID2_);
			break;
		default:
			TRACE("–¢’m‚ÌTransitionType:%d", static_cast<int>(transitionType_));
			break;
	}
}
