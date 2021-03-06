#pragma once

#include"Item.h"
#include<memory>
namespace game_framework {
	enum SWITCH_STATUS
	{
		SWITCH_RELEASE,
		SWITCH_PRESS
	};
	class CMovingBitmap;
	class Platform;
	class Switch : public Item
	{
		//两种开关：按钮（非持续作用 500 switch_button）、拉杆（持续作用 501 switch_stick）//
		//拉杆底座视为墙壁，在拉杆下方一格

	public:
		Switch(int type, int x, int y);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
		//开关绑定平台
		void Bind(shared_ptr<Platform> platform);
		void Trigger();

		//开关状态
		int status = 0;
		bool is_on = false;
	private:
		CMovingBitmap bitmap_switch_on;
		CMovingBitmap bitmap_switch_off;

		//开关绑定的平台
		shared_ptr<Platform> bind_platform;
	};
}