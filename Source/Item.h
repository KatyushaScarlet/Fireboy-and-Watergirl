#pragma once

namespace game_framework {
	class Item
	{
	public:
		~Item() {};
		void LoadBitmap();
		void OnShow();//显示
		void OnMove();//移动
		void Interact();//与其他物件交互
		int  GetX1();			//左上角 x 坐标
		int  GetY1();			//左上角 y 坐标
		int  GetX2();			//右下角 x 坐标
		int  GetY2();			//右下角 y 坐标
		bool GetAccessibility();//获取通行性
	protected:
		int x1, y1, x2, y2;//左上角坐标
		bool is_accessible();//是否可通过
	};
}