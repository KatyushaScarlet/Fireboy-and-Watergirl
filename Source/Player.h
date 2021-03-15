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
		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		void Initialize();		//设定为初始值
		void LoadBitmap();		//载入图形
		void OnMove(Map* m);	//移动
		void OnShow(Map* map);	//显示
		void SetTopLeft(int top, int left);
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测
		bool is_boy;			//是否是男孩
		int x;			//左上角x坐标
		int y;			//左上角y坐标
	};
}