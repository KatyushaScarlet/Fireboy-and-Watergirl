#pragma once

#include "Item.h"

#include <memory>

namespace game_framework {
	class Pool :public Item
	{
	public:
		Pool(int type);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
	protected:
		CAnimation animation_pool;
		CMovingBitmap bitmap_wall;
	private:
		void AddAnimationBitmap(string path);
	};
}