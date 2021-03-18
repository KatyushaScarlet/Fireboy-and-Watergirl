#pragma once

#define	PLAYER_SIZE_WIDTH 1
#define PLAYER_SIZE_HEIGHT 2
#define PLAYER_GIRD_PIXEL 32

#include "gamelib.h"
#include "Map.h"

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
		Player(bool boy);
		~Player();
		void Initialize();		//�趨Ϊ��ʼֵ
		void LoadBitmap();		//����ͼ��
		void OnMove(Map* map);	//�ƶ�
		void OnShow(Map* map);	//��ʾ
		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
		void SetXY(int x, int y);		// �趨���Ͻ�����
		void SetPlayerState(int vertical,int horizontal);	// �趨�ƶ���״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���
	private:
		int  x, y;			//���Ͻ�����
		int  initial_velocity;	// ��ʼ�ٶ�
		int  velocity;			// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;				// �Ƿ����к�����
		int moving_state;			// ��ȡ�ƶ���״̬
		bool isInvicible;			// �Ƿ�ɼ�
		bool isAlive;				// �Ƿ����
		CAnimation animation;		// ����
	};
}