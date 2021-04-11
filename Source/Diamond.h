#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Diamond : public Item
	{
	public:
		Diamond(int type);
		void LoadItemBitmap();
		void OnShow();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
	protected:
		CMovingBitmap bitmap;
	};
}