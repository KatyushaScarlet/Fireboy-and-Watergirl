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
		CMovingBitmap bitmap_pause0;
		CMovingBitmap bitmap_pause1;
		CMovingBitmap bitmap_over;

		int top = 0;
		int left = 0;
	};
}