#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Wall : public Item
	{
	public:
		Wall();
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
		void Interact(Map* m, bool is_boy, int direction);
	protected:
		CMovingBitmap bitmap;
	};
}