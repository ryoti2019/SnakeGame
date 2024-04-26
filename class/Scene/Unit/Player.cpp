#include <DxLib.h>
#include "Player.h"
#include "../Map.h"

Player::Player()
{

}

Player::~Player()
{
}

bool Player::Init(int id, CharID charID,int chipSize, State state)
{
	chipSize_ = chipSize;
	state_ = state;

	if (id == 0)
	{
		// 1P
		pos_.x = chipSize * 5;
		pos_.y = chipSize * 5;
		keyList_[static_cast<int>(Dir::Left)] = KEY_INPUT_A;
		keyList_[static_cast<int>(Dir::Right)] = KEY_INPUT_D;
		keyList_[static_cast<int>(Dir::Up)] = KEY_INPUT_W;
		keyList_[static_cast<int>(Dir::Down)] = KEY_INPUT_S;
		dir_ = Dir::Right;
	}
	else
	{
		// 2P
		pos_.x = chipSize * (MAP_CHIP_COUNT_X - 5);
		pos_.y = chipSize * 5;
		keyList_[static_cast<int>(Dir::Left)] = KEY_INPUT_LEFT;
		keyList_[static_cast<int>(Dir::Right)] = KEY_INPUT_RIGHT;
		keyList_[static_cast<int>(Dir::Up)] = KEY_INPUT_UP;
		keyList_[static_cast<int>(Dir::Down)] = KEY_INPUT_DOWN;
		dir_ = Dir::Left;
	}

	return false;
}

bool Player::Release(void)
{
	return true;
}

void Player::Update(MapCtl* mapCtl)
{

	SetDir();

	if ((pos_.x % chipSize_) == 0 &&
		(pos_.y % chipSize_) == 0)
	{
		if (mapCtl->isOnBlock(pos_))
		{
			state_ = State::Dead;
			return;
		}
		mapCtl->SetBlock(pos_, 1);
	}

	// à⁄ìÆêßå‰
	switch (dir_)
	{
	case Dir::Left:
		pos_.x -= 2;
		break;
	case Dir::Right:
		pos_.x += 2;
		break;
	case Dir::Up:
		pos_.y -= 2;
		break;
	case Dir::Down:
		pos_.y += 2;
		break;
	}
}

Player::State Player::GetState(void)
{
	return state_;
}

bool Player::SetState(State state)
{
	if (state < State::Non || state >= State::Max)
	{
		return false;
	}
	state_ = state;
	return true;
}

bool Player::SetDir(void)
{
	if ((pos_.x % chipSize_) || (pos_.y % chipSize_))
	{
		return false;
	}

	// ï˚å¸êßå‰
	if (keyNow_[static_cast<int>(Dir::Left)])
	{
		dir_ = Dir::Left;
	}
	if (keyNow_[static_cast<int>(Dir::Right)])
	{
		dir_ = Dir::Right;
	}
	if (keyNow_[static_cast<int>(Dir::Up)])
	{
		dir_ = Dir::Up;
	}
	if (keyNow_[static_cast<int>(Dir::Down)])
	{
		dir_ = Dir::Down;
	}
	return true;
}

void Player::Draw(void)
{
	DrawGraph(
		pos_.x,
		pos_.y - chipSize_ / 3,
		charImage_->chipImage_[static_cast<int>(dir_)][0],
		true
	);
}

void Player::SetCharImage(CharImage* charImage)
{
	charImage_ = charImage;
}

const CharImage* Player::GetCharImage(void)
{
	return charImage_;
}

void Player::GetKeyState(char* keyData)
{
	memcpy(keyOld_, keyNow_, sizeof(keyOld_));
	for (int dir = 0; dir < static_cast<int>(Dir::Max); dir++)
	{
		keyNow_[dir] = keyData[keyList_[dir]];
	}
}

CharID Player::GetCharID(void)
{
	return charImage_->GetID();
}
