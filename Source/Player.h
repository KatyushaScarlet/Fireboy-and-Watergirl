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
		void Initialize();		//设定为初始值
		void LoadBitmap();		//载入图形
		void OnMove(Map* map);	//移动
		void OnShow(Map* map);	//显示
		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		//int  GetX2();			//右下角 x 坐标
		//int  GetY2();			//右下角 y 坐标
		void SetTopLeft(int top, int left);// 设定左上角座标
		void SetXY(int nx, int ny);		// 设定左上角坐标
		void SetMovingState(int player_state);	// 设定移动的状态
	private:
		int  x, y;			//左上角坐标
		int  initial_velocity;	// 初始速度
		int  velocity;			// 目前的速度(pixel/frame)
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测
		bool is_boy;				// 是否是男孩（火）
		int getMovingState;			// 获取移动的状态
		bool isInvicible;			// 是否可见
		bool isAlive;				// 是否活着
		CAnimation animation;		// 动画
	};
}