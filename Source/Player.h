#pragma once


namespace game_framework {
	class Map;
	class Player
	{
	public:
		Player(bool boy);
		~Player();
		void LoadBitmapPlayer();//载入图形
		void OnMove(Map* m);//移动
		void OnShow();//显示
		int  GetCenterX();//获取中心点x
		int  GetCenterY();//获取中心点y
		int  GetX1();//获取左上角x
		int  GetY1();//获取左上角y
		int  GetX2();//获取右下角x
		int  GetY2();//获取右下角y
		void SetTopLeft(int top, int left);// 设定左上角坐标
		void SetVerticalState(int state);//设定垂直状态
		void SetHorizontalState(int state);//设定水平状态
		int GetVerticalState();//获取垂直状态
		int GetHorizontalState();//获取水平状态
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测

	private:
		int x, y;//左上角坐标
		int moving_vertical, moving_horizontal;//移动的状态
		int  initial_velocity;// 初始速度
		int  velocity;// 目前的速度(pixel/frame)
		bool is_boy;// 是否是男孩（火）
		bool is_visible;// 是否可见
		CMovingBitmap bitmap;// 静止图像
	};
}