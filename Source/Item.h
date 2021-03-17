#pragma once

namespace game_framework {
	class Item
	{
	public:
		virtual ~Item() {};
		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;//显示
		virtual void OnMove() = 0;//移动
		virtual void Interact() = 0;//与其他物件交互
	};
}