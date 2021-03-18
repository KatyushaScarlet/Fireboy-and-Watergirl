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
		void LoadBitmapPlayer()		//载入图形
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
		void OnMove()	//移动
		{
			switch (vertical)
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

			switch (horizontal)
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
		void OnShow()	//显示
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
				bitmap.ShowBitmap();
			}
		};

		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		void SetTopLeft(int top, int left)		// 设定左上角坐标
		{
			x = left;
			y = top;
		}
		void SetState(int vertical,int horizontal);	// 设定移动的状态
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测

	private:
		int x, y;//坐标
		int vertical, horizontal;//移动的状态
		int  initial_velocity;	// 初始速度
		int  velocity;			// 目前的速度(pixel/frame)
		bool is_boy;				// 是否是男孩（火）
		//int moving_state = 			// 获取移动的状态
		bool is_visible;			// 是否可见
		//bool is_alive;				// 是否活着
		CMovingBitmap bitmap;		// 静止图像
	};
}