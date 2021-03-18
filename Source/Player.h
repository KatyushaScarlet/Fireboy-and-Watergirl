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
			Initialize();
		};
		~Player()
		{

		};
		void Initialize()		//初始化
		{
			x1 = 0;
			y1 = 0;
			initial_velocity = 0;
			velocity = 0;
			is_visible = true;
			LoadBitmap();
		};
		void LoadBitmap()		//载入图形
		{
			if (is_boy)
			{
				bitmap.LoadBitmapA("RES\\player\\boy_static.bmp");
			}
			else
			{
				bitmap.LoadBitmapA("RES\\player\\girl_static.bmp");
			}
		};
		void OnMove();	//移动
		void OnShow()	//显示
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x1, y1);
				bitmap.ShowBitmap();
			}
		};

		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		void SetTopLeft(int x, int y)		// 设定左上角坐标
		{
			x1 = x;
			y1 = y;
		}
		void SetState(int vertical,int horizontal);	// 设定移动的状态
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测

	private:
		int x1, y1;//坐标
		int  initial_velocity;	// 初始速度
		int  velocity;			// 目前的速度(pixel/frame)
		bool is_boy;				// 是否是男孩（火）
		//int moving_state = 			// 获取移动的状态
		bool is_visible;			// 是否可见
		//bool is_alive;				// 是否活着
		CMovingBitmap bitmap;		// 静止图像

	};
}