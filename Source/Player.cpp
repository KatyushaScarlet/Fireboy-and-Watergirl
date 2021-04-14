#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateRun.h"
#include "Player.h"

namespace game_framework {
	class Map;
	Player::Player(bool boy)
	{
		score = 0;
		is_boy = boy;
		x = 0;
		y = 0;
		moving_vertical = DIRECTION_NONE;
		moving_horizontal = DIRECTION_NONE;
		velocity = INITIAL_VELOCITY;
		is_visible = true;

		is_die = false;
		reach_exit = false;
	};
	Player::~Player()
	{

	};
	void Player::LoadBitmapPlayer()//载入图形
	{
		if (is_boy)
		{
			//bitmap.LoadBitmapA("RES\\player\\boy_static.bmp", RGB(255, 255, 255));
			animation_static.AddBitmap("RES\\player\\boy_static0.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\boy_static1.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\boy_static2.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\boy_static3.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\boy_static4.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\boy_left0.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\boy_left1.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\boy_left2.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\boy_left3.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\boy_left4.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\boy_right0.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\boy_right1.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\boy_right2.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\boy_right3.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\boy_right4.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\boy_up0.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\boy_up1.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\boy_up2.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\boy_down0.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\boy_down1.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\boy_down2.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\boy_down3.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\boy_down4.bmp", RGB(0, 0, 0));
			charactor_ani = &animation_static;
			charactor_ani->SetDelayCount(3);
		}
		else
		{
			//bitmap.LoadBitmapA("RES\\player\\girl_static.bmp", RGB(255, 255, 255));
			animation_static.AddBitmap("RES\\player\\girl_static0.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\girl_static1.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\girl_static2.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\girl_static3.bmp", RGB(0, 0, 0));
			animation_static.AddBitmap("RES\\player\\girl_static4.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\girl_left0.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\girl_left1.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\girl_left2.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\girl_left3.bmp", RGB(0, 0, 0));
			animation_left.AddBitmap("RES\\player\\girl_left4.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\girl_right0.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\girl_right1.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\girl_right2.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\girl_right3.bmp", RGB(0, 0, 0));
			animation_right.AddBitmap("RES\\player\\girl_right4.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\girl_up0.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\girl_up1.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\girl_up2.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\girl_up3.bmp", RGB(0, 0, 0));
			animation_up.AddBitmap("RES\\player\\girl_up4.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\girl_down0.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\girl_down1.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\girl_down2.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\girl_down3.bmp", RGB(0, 0, 0));
			animation_down.AddBitmap("RES\\player\\girl_down4.bmp", RGB(0, 0, 0));
			charactor_ani = &animation_static;
			charactor_ani->SetDelayCount(3);
		}
	};

	void Player::OnMove()
	{
		animation_static.OnMove();
		animation_left.OnMove();
		animation_right.OnMove();
		animation_down.OnMove();
		animation_up.OnMove();

	}

	void Player::OnShow()//显示
	{
		animation_static.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
		animation_down.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
		animation_up.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
		animation_left.SetTopLeft(x , y - PLAYER_GIRD_PIXEL);
		animation_right.SetTopLeft(x - PLAYER_GIRD_PIXEL, y - PLAYER_GIRD_PIXEL);

		if (is_visible)
		{
			charactor_ani->OnShow();
		}
	};

	int  Player::GetX1()
	{
		return x;
	}
	int Player::GetY1()
	{
		return y;
	}
	int  Player::GetX2()
	{
		return x + PLAYER_GIRD_PIXEL;
	}
	int Player::GetY2()
	{
		return y + PLAYER_GIRD_PIXEL;
	}
	int Player::GetVelocity()
	{
		return velocity;
	}
	int Player::GetStep()
	{
		return PLAYER_STEP_PIXEL;
	}
	void Player::SetTopLeft(int top, int left)// 设定左上角坐标
	{
		x = left;
		y = top;
	}
	void Player::SetVerticalState(int state)//设定垂直状态
	{
		moving_vertical = state;
	}
	void Player::SetHorizontalState(int state)//设定水平状态
	{
		moving_horizontal = state;
	}
	int Player::GetVerticalState()//获取垂直状态
	{
		return moving_vertical;
	}
	int Player::GetHorizontalState()//获取水平状态
	{
		return moving_horizontal;
	}
	CAnimation& Player::GetStatic()
	{
		return animation_static;
	}
	CAnimation& Player::GetLeft()
	{
		return animation_left;
	}
	CAnimation& Player::GetRight()
	{
		return animation_right;
	}
	CAnimation& Player::GetUp()
	{
		return animation_up;
	}
	CAnimation& Player::GetDown()
	{
		return animation_down;
	}
	void Player::SetAni(CAnimation& ani)
	{
		charactor_ani = &ani;
	}
};