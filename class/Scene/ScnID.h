#pragma once

enum class TransitionType
{
	Non,
	FadeIn,
	FadeInOut,
	Max
};

enum class ScnID
{
	Non,			// ����������
	Logo,
	Title,
	Select,
	Game,
	Result,
	Transition,
	Max
};

struct NextScnID
{
	ScnID id;
	TransitionType transitionType;
};


