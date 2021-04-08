#pragma once


namespace game_framework {
	class Map;
	class Player
	{
	public:
		Player(bool boy);
		~Player();
		void LoadBitmapPlayer();//载入图形
		void OnMove(CGameStateRun* game);//移动
		void OnShow();//显示
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		int GetVelocity();
		int GetStep();
		void SetTopLeft(int top, int left);// 设定左上角坐标
		void SetVerticalState(int state);//设定垂直状态
		void SetHorizontalState(int state);//设定水平状态
		int GetVerticalState();//获取垂直状态
		int GetHorizontalState();//获取水平状态
		//bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//碰撞检测

		bool is_boy;// 是否是男孩（火）
		bool is_visible;// 是否可见
		bool is_die;//是否死亡
		bool reach_exit;//到达出口

	private:
		int x, y;//坐标
		int moving_vertical, moving_horizontal;//移动的状态
		int  velocity;// 目前的速度(pixel/frame)
		CMovingBitmap bitmap;// 静止图像
	};
}