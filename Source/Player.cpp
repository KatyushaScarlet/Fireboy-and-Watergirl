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
#define MOVE_OFFSET 2
namespace game_framework {
	class Map;
	Player::Player(bool boy)
	{
		is_boy = boy;
		x = 0;
		y = 0;
		moving_vertical = DIRECTION_NONE;
		moving_horizontal = DIRECTION_NONE;
		initial_velocity = 16;
		velocity = initial_velocity;
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
	void Player::OnMove(Map* map)//移动
	{
		bool can_move = false;

		if (moving_vertical == DIRECTION_UP)
		{
			//上升状态
			//TRACE("up\n");
			can_move = (map->PlayerCanMove(GetX1(), GetY1() - PLAYER_GIRD_PIXEL, DIRECTION_UP)&& map->PlayerCanMove(GetX2(), GetY1() - PLAYER_GIRD_PIXEL, DIRECTION_UP));//判断上方与右上
			if (can_move && velocity > 0)//如果上方可通行，垂直速度大于0
			{
				y -= velocity;
				velocity--;
			}
			else
			{
				moving_vertical = DIRECTION_DOWN;//当速度<=0时，垂直方向变为下降
				velocity = 1;
			}
		}
		else
		{
			//如果非上升状态，始终判断是否下落
			//TRACE("down\n");
			can_move = (map->PlayerCanMove(GetX1(), GetY2(), DIRECTION_DOWN) && map->PlayerCanMove(GetX2(), GetY2(), DIRECTION_DOWN));//判断下方与右下
			if (can_move)//如果下方可通行
			{
				y += velocity;
				if (velocity < 5)//防止下落速度过大
				{
					velocity++;
				}

			}
			else
			{
				moving_vertical = DIRECTION_NONE;//当下方不可通行时，垂直方向变成静止
				velocity = initial_velocity;//加速度变为初始值
			}
		}

		switch (moving_horizontal)//水平移动
		{

		case DIRECTION_LEFT:
			//TRACE("left\n");
			can_move = map->PlayerCanMove(GetX1() + MOVE_OFFSET - PLAYER_STEP_PIXEL, GetY1(), DIRECTION_LEFT);
			if (can_move) {
				x -= PLAYER_STEP_PIXEL;
			}
			break;
		case DIRECTION_RIGHT: {
			//TRACE("right\n");
			can_move = map->PlayerCanMove(GetX2() - MOVE_OFFSET + PLAYER_STEP_PIXEL, GetY1(), DIRECTION_RIGHT);
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
		return y + PLAYER_GIRD_PIXEL;
	}
	int  Player::GetX2()
	{
		return x + PLAYER_GIRD_PIXEL;
	}
	int Player::GetY2()
	{
		return y + PLAYER_GIRD_PIXEL + PLAYER_GIRD_PIXEL;
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
	bool Player::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		return false;
	}//碰撞检测
};