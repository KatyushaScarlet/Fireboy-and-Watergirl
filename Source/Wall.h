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
		bool Interact();
	protected:
		CMovingBitmap bitmap;
		//for test
		CMovingBitmap test_bitmap;
		bool test_flag;
	};
}