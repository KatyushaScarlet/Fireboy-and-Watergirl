#pragma once

namespace game_framework {
	class CMovingBitmap;
	class Menu
	{
	public:
		Menu();
		void LoadItemBitmap();
		void OnShow(int menuType);
		void OnMove(int menuType);
	private:
		CMovingBitmap bitmap_pause;
		CMovingBitmap bitmap_over;

		int top = 159;
		int left = 99;
	};
}