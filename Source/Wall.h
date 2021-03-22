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
	protected:
		CMovingBitmap bitmap;
	};
}