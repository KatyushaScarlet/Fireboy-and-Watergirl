#pragma once

#define	PLAYER_SIZE_WIDTH 1
#define PLAYER_SIZE_HEIGHT 2
#define PLAYER_GIRD_PIXEL 32

#include "gamelib.h"

namespace game_framework {

	class Player
	{
	public:
		Player(bool boy);
		~Player();
		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
		void Initialize();		//�趨Ϊ��ʼֵ
		void LoadBitmap();		//����ͼ��
		void OnMove(Map* m);	//�ƶ�
		void OnShow(Map* map);	//��ʾ
		void SetTopLeft(int top, int left);
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���
		bool is_boy;			//�Ƿ����к�
		int x;			//���Ͻ�x����
		int y;			//���Ͻ�y����
	};
}