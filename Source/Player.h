#pragma once

#define PLAYER_GIRD_PIXEL 32
#define PLAYER_STEP_PIXEL 4

#include "gamelib.h"

namespace game_framework {

	enum DIRECTIONS
	{
		DIRECTION_NONE,
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_RIGHT,
		DIRECTION_LEFT
	};

	class Player
	{
	public:
		Player(bool boy)
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
		void OnMove()//�ƶ�
		{
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
				x -= PLAYER_STEP_PIXEL;
				break;
			case DIRECTION_RIGHT:
				x += PLAYER_STEP_PIXEL;
				break;
			case DIRECTION_NONE:
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