#pragma once

#include"Item.h"

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
		void Interact(CGameStateRun* game, bool is_boy, int direction);
		//开关绑定平台
		void Bind(Platform* platform);
	protected:
		CMovingBitmap bitmap_switch_on;
		CMovingBitmap bitmap_switch_off;
	private:
		//开关状态
		int status = 0;
		bool is_on = false;
		//开关绑定的平台
		Platform* bind_platform;
	};
}