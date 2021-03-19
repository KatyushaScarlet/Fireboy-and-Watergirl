#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "Player.h"

#define PLAYER_GIRD_PIXEL 32
#define PLAYER_STEP_PIXEL 4

namespace game_framework {
	class Map;
	Player::Player(bool boy)
	{
		is_boy = boy;
		x = 0;
		y = 0;
		moving_vertical = DIRECTION_NONE;
		moving_horizontal = DIRECTION_NONE;
		initial_velocity = 10;
		velocity = 0;
		is_visible = true;
	};
	Player::~Player()
	{

	};
	void Player::LoadBitmapPlayer()//载入图形
	{
		if (is_boy)
		{
			bitmap.LoadBitmapA("RES\\player\\boy_static.bmp", RGB(255, 255, 255));
		}
		else
		{
			bitmap.LoadBitmapA("RES\\player\\girl_static.bmp", RGB(255, 255, 255));
		}
	};
	void Player::OnMove(Map *m)//移动
	{
		
		switch (moving_vertical)//垂直移动
		{
		case DIRECTION_UP://上升状态
			if (velocity > 0)
			{
				y -= velocity;//当速度>0时上升
				velocity--;
			}
			else
			{
				moving_vertical = DIRECTION_DOWN;//当速度<=0时，垂直方向变为下降
				velocity = 1;
			}
			break;
		case DIRECTION_DOWN://下降状态
			if (true)//如果下方可通行
			{
				y += velocity;
				velocity++;
			}
			else
			{
				moving_vertical = DIRECTION_NONE;//当下方不可通行时，垂直方向变成静止
				velocity = initial_velocity;//加速度变为初始值
			}
			break;
		case DIRECTION_NONE:
			break;
		default:
			break;
		}

		switch (moving_horizontal)//水平移动
		{
		case DIRECTION_LEFT:
			x -= PLAYER_STEP_PIXEL;
			break;
		case DIRECTION_RIGHT:{
			bool can_move = m->PlayerCanMove(GetX2(), GetY1(), DIRECTION_RIGHT);
			if (can_move) {
				x += PLAYER_STEP_PIXEL;
			}
			
			break;
		}
		case DIRECTION_NONE:
			break;
		default:
			break;
		}
	}

	void Player::OnShow()//显示
	{
		bitmap.SetTopLeft(x, y);
		if (is_visible)
		{
			bitmap.ShowBitmap();
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
		return y + 2 * PLAYER_GIRD_PIXEL;
	}
	void Player::SetTopLeft(int top, int left)// 设定左上角坐标
	{
		x = left;
		y = top - PLAYER_GIRD_PIXEL;//人物为2格高
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
	bool Player::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		return false;
	}//碰撞检测
};