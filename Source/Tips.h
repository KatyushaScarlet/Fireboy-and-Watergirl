#pragma once

#include "Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Tips : public Item
	{
	public:
		Tips(string name, int x, int y);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
	private:
		CMovingBitmap bitmap;
		
		string name;
	};
}