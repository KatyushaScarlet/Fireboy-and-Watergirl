#pragma once

#include "Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Box : public Item
	{
	public:
		Box();
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
	private:
		CMovingBitmap bitmap;
	};
}