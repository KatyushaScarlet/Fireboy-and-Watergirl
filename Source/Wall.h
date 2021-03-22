#pragma once


namespace game_framework {

	class Wall
	{
	public:
		Wall()
		{
			width = 1;
			height = 1;
			is_accessible = false;
		}
		virtual void LoadItemBitmap()
		{
			bitmap.LoadBitmapA("RES\\wall.bmp");
		}
		void OnShow()
		{
			bitmap.SetTopLeft(y, x);
			bitmap.ShowBitmap();
		}
		void OnMove();
		void SetTopLeft(int top, int left)// 设定左上角坐标
		{
			x = left;
			y = top;
		}
		int  GetX1()			//左上角 x 坐标
		{
			return x;
		}
		int  GetY1()			//左上角 y 坐标
		{
			return y;
		}
		int  GetX2()			//右下角 x 坐标
		{
			return x + width;
		}
		int  GetY2()			//右下角 y 坐标
		{
			return y + height;
		}
		bool GetAccessible()//是否可以通过
		{
			return is_accessible;
		}
		bool HitRectangle(int x1, int y1, int x2, int y2)//是否相撞
		{
			return (GetX2() >= x1 && x <= x2 && GetY2() >= y1 && y <= y2);
		}
	protected:
		int x, y;//左上角坐标
		int width;
		int height;
		bool is_accessible;//是否可通过
		CMovingBitmap bitmap;
	};
}