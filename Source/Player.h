#pragma once

#define PLAYER_GIRD_PIXEL 32

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
		PLAYER_STATES_HORIZONTAL_MOVE_RIGHT,
	};

	class Player
	{
	public:
		Player(bool boy)
		{
			is_boy = boy;
			//Initialize();
			x1 = 0;
			y1 = 0;
			initial_velocity = 0;
			velocity = 0;
			is_visible = true;
		};
		~Player()
		{

		};
		//void Initialize()		//��ʼ��
		//{
		//	x1 = 0;
		//	y1 = 0;
		//	initial_velocity = 0;
		//	velocity = 0;
		//	is_visible = true;
		//	LoadBitmap();
		//};
		void LoadBitmapPlayer()		//����ͼ��
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
		void OnMove();	//�ƶ�
		void OnShow()	//��ʾ
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x1, y1 - PLAYER_GIRD_PIXEL);
				bitmap.ShowBitmap();
			}
		};

		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
		void SetTopLeft(int x, int y)		// �趨���Ͻ�����
		{
			x1 = x;
			y1 = y;
		}
		void SetState(int vertical,int horizontal);	// �趨�ƶ���״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x1, y1;//����
		int  initial_velocity;	// ��ʼ�ٶ�
		int  velocity;			// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;				// �Ƿ����к�����
		//int moving_state = 			// ��ȡ�ƶ���״̬
		bool is_visible;			// �Ƿ�ɼ�
		//bool is_alive;				// �Ƿ����
		CMovingBitmap bitmap;		// ��ֹͼ��

	};
}