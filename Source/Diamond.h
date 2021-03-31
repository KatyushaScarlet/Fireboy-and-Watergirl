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
		void OnMove();
		void Interact(Map* m, bool is_boy);
	protected:
		CMovingBitmap bitmap;
	};
}