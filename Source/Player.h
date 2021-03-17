#pragma once

#define	PLAYER_SIZE_WIDTH 1
#define PLAYER_SIZE_HEIGHT 2
#define PLAYER_GIRD_PIXEL 32

#include "gamelib.h"
#include "Map.h"

namespace game_framework {

	enum PLAYER_STATES {
		PLAYER_STATES_STATIC,
		PLAYER_STATES_MOVE_LEFT,
		PLAYER_STATES_MOVE_RIGHT,
		PLAYER_STATES_MOVE_UP,
		PLAYER_STATES_MOVE_DOWN,
	};

	class Player
	{
	public:
		Player(bool boy);
		~Player();
		void Initialize();		//�趨Ϊ��ʼֵ
		void LoadBitmap();		//����ͼ��
		void OnMove(Map* map);	//�ƶ�
		void OnShow(Map* map);	//��ʾ
		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		//int  GetX2();			//���½� x ����
		//int  GetY2();			//���½� y ����
		void SetTopLeft(int top, int left);// �趨���Ͻ�����
		void SetXY(int nx, int ny);		// �趨���Ͻ�����
		void SetMovingState(int player_state);	// �趨�ƶ���״̬
	private:
		int  x, y;			//���Ͻ�����
		int  initial_velocity;	// ��ʼ�ٶ�
		int  velocity;			// Ŀǰ���ٶ�(pixel/frame)
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���
		bool is_boy;				// �Ƿ����к�����
		int getMovingState;			// ��ȡ�ƶ���״̬
		bool isInvicible;			// �Ƿ�ɼ�
		bool isAlive;				// �Ƿ����
		CAnimation animation;		// ����
	};
}