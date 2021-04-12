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
			bitmap.LoadBitmapA("RES\\player\\boy_static.bmp", RGB(255, 255, 255));
		}
		else
		{
			bitmap.LoadBitmapA("RES\\player\\girl_static.bmp", RGB(255, 255, 255));
		}
	};

	void Player::OnMove()
	{

	}

	//void Player::OnMove(CGameStateRun* game)//移动
	//{
	//	bool can_move;

	//	if (moving_vertical == DIRECTION_UP)
	//	{
	//		can_move = game->CanMove(this, DIRECTION_UP);
	//		//上升状态
	//		//TRACE("up\n");
	//		if (can_move && velocity > 0)//如果上方可通行，垂直速度大于0
	//		{
	//			y -= velocity;
	//			velocity--;
	//		}
	//		else
	//		{
	//			moving_vertical = DIRECTION_DOWN;//当速度<=0时，垂直方向变为下降
	//			velocity = 1;
	//		}
	//	}
	//	else
	//	{
	//		//如果非上升状态，始终判断是否下落
	//		//TRACE("down\n");
	//		can_move = game->CanMove(this, DIRECTION_DOWN);
	//		if (can_move)//如果下方可通行
	//		{
	//			moving_vertical = DIRECTION_DOWN;
	//			y += velocity;
	//			if (velocity < 5)//防止下落速度过大
	//			{
	//				velocity++;
	//			}
	//			else
	//			{
	//				velocity = 4;//fixbug:当直接掉下时初速度为 INITIAL_VELOCITY （跳起初始速度） 而不是1（掉落初始速度）
	//			}
	//		}
	//		else
	//		{
	//			moving_vertical = DIRECTION_NONE;//当下方不可通行时，垂直方向变成静止
	//			velocity = INITIAL_VELOCITY;//加速度变为初始值
	//		}
	//	}

	//	switch (moving_horizontal)//水平移动
	//	{

	//	case DIRECTION_LEFT:
	//		can_move= game->CanMove(this, DIRECTION_LEFT);
	//		if (can_move) {
	//			x -= PLAYER_STEP_PIXEL;
	//		}
	//		break;
	//	case DIRECTION_RIGHT: {
	//		can_move = game->CanMove(this, DIRECTION_RIGHT);
	//		if (can_move) {
	//			x += PLAYER_STEP_PIXEL;
	//		}

	//		break;
	//	}
	//	case DIRECTION_NONE:
	//		break;
	//	default:
	//		break;
	//	}
	//}

	void Player::OnShow()//显示
	{
		bitmap.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
		//bitmap.SetTopLeft(x, y);
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
		return y + PLAYER_GIRD_PIXEL;
		//return y + PLAYER_GIRD_PIXEL * 2;
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
	//bool Player::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
	//	return false;
	//}//碰撞检测
};