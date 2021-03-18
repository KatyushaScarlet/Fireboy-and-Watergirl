#pragma once

#define PLAYER_GIRD_PIXEL 32
#define PLAYER_STEP_PIXEL 4

#include "gamelib.h"

namespace game_framework {

	enum PLAYER_STATES_VERTICAL  
	{
		PLAYER_STATES_VERTICAL_MOVE_UP,
		PLAYER_STATES_VERTICAL_MOVE_DOWN,
		PLAYER_STATES_VERTICAL_STATIC
	};

	enum PLAYER_STATES_HORIZONTAL
	{
		PLAYER_STATES_HORIZONTAL_MOVE_LEFT,
		PLAYER_STATES_HORIZONTAL_MOVE_RIGHT,
		PLAYER_STATES_HORIZONTAL_STATIC
	};

	class Player
	{
	public:
		Player(bool boy)
		{
			is_boy = boy;
			//Initialize();
			x = 0;
			y = 0;
			initial_velocity = 0;
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
			switch (vertical)//��ֱ�ƶ�
			{
			case PLAYER_STATES_VERTICAL_MOVE_UP:
				y -= PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_VERTICAL_MOVE_DOWN:
				y += PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_VERTICAL_STATIC:
				break;
			default:
				break;
			}

			switch (horizontal)//ˮƽ�ƶ�
			{
			case PLAYER_STATES_HORIZONTAL_MOVE_LEFT:
				x -= PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_MOVE_RIGHT:
				x += PLAYER_GIRD_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_STATIC:
				break;
			default:
				break;
			}
		}
		void OnShow()//��ʾ
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
				bitmap.ShowBitmap();
			}
		};

		int  GetX1();//���Ͻ� x ����
		int  GetY1();//���Ͻ� y ����
		int  GetX2();//���½� x ����
		int  GetY2();//���½� y ����
		void SetTopLeft(int top, int left)// �趨���Ͻ�����
		{
			x = left;
			y = top;
		}
		void SetState(int vertical,int horizontal);// �趨�ƶ���״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x, y;//����
		int vertical, horizontal;//�ƶ���״̬
		int  initial_velocity;// ��ʼ�ٶ�
		int  velocity;// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;// �Ƿ����к�����
		//int moving_state = // ��ȡ�ƶ���״̬
		bool is_visible;// �Ƿ�ɼ�
		//bool is_alive;// �Ƿ����
		CMovingBitmap bitmap;// ��ֹͼ��
	};
}