#pragma once

#define PLAYER_GIRD_PIXEL 32
#define PLAYER_STEP_PIXEL 4

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
		PLAYER_STATES_HORIZONTAL_MOVE_RIGHT
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
			moving_vertical = PLAYER_STATES_VERTICAL_STATIC;
			moving_horizontal = PLAYER_STATES_HORIZONTAL_STATIC;
			initial_velocity = 0;
			velocity = 0;
			is_visible = true;
		};
		~Player()
		{

		};
		void LoadBitmapPlayer()//载入图形
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
		void OnMove()//移动
		{
			switch (moving_vertical)//垂直移动
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

			switch (moving_horizontal)//水平移动
			{
			case PLAYER_STATES_HORIZONTAL_MOVE_LEFT:
				x -= PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_MOVE_RIGHT:
				x += PLAYER_STEP_PIXEL;
				break;
			case PLAYER_STATES_HORIZONTAL_STATIC:
				break;
			default:
				break;
			}
		}
		void OnShow()//显示
		{
			if (is_visible)
			{
				bitmap.SetTopLeft(x, y - PLAYER_GIRD_PIXEL);
				bitmap.ShowBitmap();
			}

		};

		int  GetX1()
		{
			return x;
		}
		int  GetY1()
		{
			return y;
		}
		int  GetX2()
		{
			return x + PLAYER_GIRD_PIXEL;
		}
		int  GetY2()
		{
			return y + PLAYER_GIRD_PIXEL;
		}
		void SetTopLeft(int top, int left)// 设定左上角坐标
		{
			x = left;
			y = top;
		}
		void SetVerticalState(int state)//设定垂直状态
		{
			moving_vertical = state;
		}
		void SetHorizontalState(int state)//设定水平状态
		{
			moving_horizontal = state;
		}
		int GetVerticalState()//获取垂直状态
		{
			return moving_vertical;
		}
		int GetHorizontalState()//获取水平状态
		{
			return moving_horizontal;
		}
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测

	private:
		int x, y;//坐标
		int moving_vertical, moving_horizontal;//移动的状态
		int  initial_velocity;// 初始速度
		int  velocity;// 目前的速度(pixel/frame)
		bool is_boy;// 是否是男孩（火）
		bool is_visible;// 是否可见
		CMovingBitmap bitmap;// 静止图像
	};
}