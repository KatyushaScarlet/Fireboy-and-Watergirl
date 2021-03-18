#pragma once

#define	PLAYER_SIZE_WIDTH 1
#define PLAYER_SIZE_HEIGHT 1
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
		};
		~Player();
		void Initialize();		//��ʼ��
		void LoadBitmap()		//����ͼ��
		{
			if (is_boy)
			{
				bitmap.LoadBitmapA("RES\\boy_static.bmp");
			}
			else
			{
				bitmap.LoadBitmapA("RES\\girl_static.bmp");
			}
		};
		void OnMove();	//�ƶ�
		void OnShow()	//��ʾ
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x1, y1);
				bitmap.ShowBitmap();
			}
		};

		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
		void SetXY(int x, int y);		// �趨���Ͻ�����
		void SetState(int vertical,int horizontal);	// �趨�ƶ���״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x1, y1, x2, y2;//����
		int  initial_velocity;	// ��ʼ�ٶ�
		int  velocity;			// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;				// �Ƿ����к�����
		int moving_state;			// ��ȡ�ƶ���״̬
		bool is_visible;			// �Ƿ�ɼ�
		bool is_alive;				// �Ƿ����
		CMovingBitmap bitmap;		// ��ֹͼ��

	};
}