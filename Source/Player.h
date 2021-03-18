#pragma once

#define PLAYER_GIRD_PIXEL 32
#define PLAYER_STEP_PIXEL 4

#include "gamelib.h"

namespace game_framework {

	enum PLAYER_STATES_VERTICAL  
	{
		PLAYER_STATES_VERTICAL_STATIC,
		PLAYER_STATES_VERTICAL_MOVE_UP,
		PLAYER_STATES_VERTICAL_MOVE_DOWN
	};

	enum PLAYER_STATES_HORIZONTAL
	{
		PLAYER_STATES_HORIZONTAL_STATIC,
		PLAYER_STATES_HORIZONTAL_MOVE_LEFT,
		PLAYER_STATES_HORIZONTAL_MOVE_RIGHT
	};

	class Player
	{
	public:
		Player(bool boy)
		{
			is_boy = boy;
			x = 0;
			y = 0;
			moving_vertical = PLAYER_STATES_VERTICAL_STATIC;
			moving_horizontal = PLAYER_STATES_HORIZONTAL_STATIC;
			initial_velocity = 10;
			velocity = 0;
			is_visible = true;
		};
		~Player()
		{

		};
		void LoadBitmapPlayer()//����ͼ��
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
		void OnMove(Map* map)//�ƶ�
		{
			bool can_move = map->PlayerCanMove(x, y, 0);

			switch (moving_vertical)//��ֱ�ƶ�
			{
			case PLAYER_STATES_VERTICAL_MOVE_UP://����״̬
				if (velocity > 0)
				{
					y -= velocity;//���ٶ�>0ʱ����
					velocity--;
				}
				else
				{
					moving_vertical = PLAYER_STATES_VERTICAL_MOVE_DOWN;//���ٶ�<=0ʱ����ֱ�����Ϊ�½�
					velocity = 1;
				}
				break;
			case PLAYER_STATES_VERTICAL_MOVE_DOWN://�½�״̬
				if (true)//����·���ͨ��
				{
					y += velocity;
					velocity++;
				}
				else
				{
					moving_vertical = PLAYER_STATES_VERTICAL_STATIC;//���·�����ͨ��ʱ����ֱ�����ɾ�ֹ
					velocity = initial_velocity;//���ٶȱ�Ϊ��ʼֵ
				}
				break;
			case PLAYER_STATES_VERTICAL_STATIC:
				break;
			default:
				break;
			}

			switch (moving_horizontal)//ˮƽ�ƶ�
			{
			case PLAYER_STATES_HORIZONTAL_MOVE_LEFT:
				x -= PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_MOVE_RIGHT:
				x += PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_STATIC:
				break;
			default:
				break;
			}
		}

		void OnShow()//��ʾ
		{
			bitmap.SetTopLeft(x, y);
			if (is_visible)
			{
				bitmap.ShowBitmap();
			}

		};

		int  GetX1()
		{
			return x;
		}
		int  GetY1()
		{
			return y;
		}
		int  GetX2()
		{
			return x + PLAYER_GIRD_PIXEL;
		}
		int  GetY2()
		{
			return y + 2 * PLAYER_GIRD_PIXEL;
		}
		void SetTopLeft(int top, int left)// �趨���Ͻ�����
		{
			x = left;
			y = top - MAP_GIRD_PIXEL;//����Ϊ2���
		}
		void SetVerticalState(int state)//�趨��ֱ״̬
		{
			moving_vertical = state;
		}
		void SetHorizontalState(int state)//�趨ˮƽ״̬
		{
			moving_horizontal = state;
		}
		int GetVerticalState()//��ȡ��ֱ״̬
		{
			return moving_vertical;
		}
		int GetHorizontalState()//��ȡˮƽ״̬
		{
			return moving_horizontal;
		}
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x, y;//����
		int moving_vertical, moving_horizontal;//�ƶ���״̬
		int  initial_velocity;// ��ʼ�ٶ�
		int  velocity;// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;// �Ƿ����к�����
		bool is_visible;// �Ƿ�ɼ�
		CMovingBitmap bitmap;// ��ֹͼ��
	};
}