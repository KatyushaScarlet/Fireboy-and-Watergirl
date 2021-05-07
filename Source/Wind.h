#pragma once

#include "Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Wind : public Item
	{
	public:
		Wind();
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
	protected:
		CAnimation bitmap;
		CMovingBitmap bitmap_wall;
	};
}