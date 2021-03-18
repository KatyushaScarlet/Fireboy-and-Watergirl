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
		void Initialize();		//设定为初始值
		void LoadBitmap();		//载入图形
		void OnMove(Map* map);	//移动
		void OnShow(Map* map);	//显示
		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		void SetXY(int x, int y);		// 设定左上角坐标
		void SetPlayerState(int vertical,int horizontal);	// 设定移动的状态
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测
	private:
		int  x, y;			//左上角坐标
		int  initial_velocity;	// 初始速度
		int  velocity;			// 目前的速度(pixel/frame)
		bool is_boy;				// 是否是男孩（火）
		int moving_state;			// 获取移动的状态
		bool isInvicible;			// 是否可见
		bool isAlive;				// 是否活着
		CAnimation animation;		// 动画
	};
}