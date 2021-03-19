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
	void Player::OnMove(Map* map)//�ƶ�
	{
		bool can_move = false;

		if (moving_vertical == DIRECTION_UP)
		{
			//����״̬
			TRACE("up\n");
			can_move = map->PlayerCanMove(GetX1(), GetY1() - PLAYER_GIRD_PIXEL, DIRECTION_UP);
			if (can_move && velocity > 0)//����Ϸ���ͨ�У���ֱ�ٶȴ���0
			{
				y -= velocity;
				velocity--;
			}
			else
			{
				moving_vertical = DIRECTION_DOWN;//���ٶ�<=0ʱ����ֱ�����Ϊ�½�
				velocity = 1;
			}
		}
		else
		{
			//���������״̬��ʼ���ж��Ƿ�����
			TRACE("down\n");
			can_move = map->PlayerCanMove(GetX1(), GetY2(), DIRECTION_DOWN);
			if (can_move)//����·���ͨ��
			{
				y += velocity;
				if (velocity < 5)//��ֹ�����ٶȹ���
				{
					velocity++;
				}

			}
			else
			{
				moving_vertical = DIRECTION_NONE;//���·�����ͨ��ʱ����ֱ�����ɾ�ֹ
				velocity = initial_velocity;//���ٶȱ�Ϊ��ʼֵ
			}
		}


		//switch (moving_vertical)//��ֱ�ƶ�
		//{
		//case DIRECTION_UP://����״̬
		//	TRACE("up\n");
		//	can_move = map->PlayerCanMove(GetX1(), GetY1() - PLAYER_GIRD_PIXEL, DIRECTION_UP);
		//	if (can_move && velocity > 0)//����Ϸ���ͨ��
		//	{
		//		y -= velocity;
		//		velocity--;

		//		//if (velocity > 0)//���ٶ�>0ʱ����
		//		//{
		//		//	y -= velocity;
		//		//	velocity--;
		//		//}
		//	}
		//	else
		//	{
		//		moving_vertical = DIRECTION_DOWN;//���ٶ�<=0ʱ����ֱ�����Ϊ�½�
		//		velocity = 1;
		//	}
		//	break;
		//case DIRECTION_DOWN://�½�״̬
		//	TRACE("down\n");
		//	can_move = map->PlayerCanMove(GetX1(), GetY2(), DIRECTION_DOWN);
		//	if (can_move)//����·���ͨ��
		//	{
		//		y += velocity;
		//		if (velocity < 10)//��ֹ�����ٶȹ���
		//		{
		//			velocity++;
		//		}

		//	}
		//	else
		//	{
		//		moving_vertical = DIRECTION_NONE;//���·�����ͨ��ʱ����ֱ�����ɾ�ֹ
		//		velocity = initial_velocity;//���ٶȱ�Ϊ��ʼֵ
		//	}
		//	break;
		//case DIRECTION_NONE:
		//	break;
		//default:
		//	break;
		//}

		switch (moving_horizontal)//ˮƽ�ƶ�
		{

		case DIRECTION_LEFT:
			TRACE("left\n");
			can_move = map->PlayerCanMove(GetX1() + MOVE_OFFSET - PLAYER_STEP_PIXEL, GetY1(), DIRECTION_LEFT);
			if (can_move) {
				x -= PLAYER_STEP_PIXEL;
			}
			break;
		case DIRECTION_RIGHT: {
			TRACE("right\n");
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
	void Player::SetTopLeft(int top, int left)// �趨���Ͻ�����
	{
		x = left;
		y = top;
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