#pragma once

#include "Item.h"
#include <string>

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
		CAnimation bitmap;
		CMovingBitmap bitmap_wall;
	private:
		void AddAnimationBitmap(string path);
	};
}