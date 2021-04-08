#pragma once

#include "Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Pool :public Item
	{
	public:
		Pool(int type);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
	protected:
		CMovingBitmap bitmap;
		CMovingBitmap bitmap_wall;
	};
}