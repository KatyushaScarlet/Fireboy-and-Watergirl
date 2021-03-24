#pragma once

namespace game_framework {
	class Map;
	class Item
	{
	public:
		virtual void LoadItemBitmap() = 0;	//加载位图
		virtual void OnShow() = 0;			//显示
		virtual void OnMove() = 0;			//移动
		virtual void Interact(Map* m) = 0;			//与其他物件交互
		void SetTopLeft(int top, int left);// 设定左上角坐标
		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		bool GetAccessible();	//是否可通过
		bool GetVisibale();		//是否可见
		bool HitRectangle(int x1, int y1, int x2, int y2);
		//是否相撞
	protected:
		int x, y;				//左上角坐标
		int width;				//宽
		int height;				//高
		bool is_accessible;		//是否可通过
		bool is_visibale;		//是否可见
	};
}