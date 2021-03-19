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
	void Player::LoadBitmapPlayer()//����ͼ��
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
	void Player::OnMove(Map *map)//�ƶ�
	{
		bool can_move = false;

		int* top = new int();
		int* left = new int();

		map->Position2ArrayIndex(x, y, top, left);

		switch (moving_vertical)//��ֱ�ƶ�
		{
		case DIRECTION_UP://����״̬
			if (velocity > 0)
			{
				y -= velocity;//���ٶ�>0ʱ����
				velocity--;
			}
			else
			{
				moving_vertical = DIRECTION_DOWN;//���ٶ�<=0ʱ����ֱ�����Ϊ�½�
				velocity = 1;
			}
			break;
		case DIRECTION_DOWN://�½�״̬
			if (true)//����·���ͨ��
			{
				y += velocity;
				velocity++;
			}
			else
			{
				moving_vertical = DIRECTION_NONE;//���·�����ͨ��ʱ����ֱ�����ɾ�ֹ
				velocity = initial_velocity;//���ٶȱ�Ϊ��ʼֵ
			}
			break;
		case DIRECTION_NONE:
			break;
		default:
			break;
		}

		switch (moving_horizontal)//ˮƽ�ƶ�
		{
		case DIRECTION_LEFT:
			TRACE("x=%d,y=%d,top=%d,left=%d\n", x, y, *top, *left);
			can_move = map->PlayerCanMove(*top, *left, DIRECTION_LEFT);
			if (can_move) {
				x -= PLAYER_STEP_PIXEL;
			}
			break;
		case DIRECTION_RIGHT:{
			TRACE("x=%d,y=%d,top=%d,left=%d\n", x, y, *top, *left);
			can_move = map->PlayerCanMove(*top, *left, DIRECTION_RIGHT);
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

	void Player::OnShow()//��ʾ
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
		return y + PLAYER_GIRD_PIXEL;
	}
	void Player::SetTopLeft(int top, int left)// �趨���Ͻ�����
	{
		x = left;
		y = top - PLAYER_GIRD_PIXEL;
	}
	void Player::SetVerticalState(int state)//�趨��ֱ״̬
	{
		moving_vertical = state;
	}
	void Player::SetHorizontalState(int state)//�趨ˮƽ״̬
	{
		moving_horizontal = state;
	}
	int Player::GetVerticalState()//��ȡ��ֱ״̬
	{
		return moving_vertical;
	}
	int Player::GetHorizontalState()//��ȡˮƽ״̬
	{
		return moving_horizontal;
	}
	bool Player::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		return false;
	}//��ײ���
};