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
		void Interact(CGameStateRun* game, bool is_boy, int direction);
	protected:
		//unique_ptr<CAnimation> animation = make_unique<CAnimation>();
		CAnimation animation_pool;
		//CMovingBitmap bitmap;
		CMovingBitmap bitmap_wall;
	private:
		void AddAnimationBitmap(string path);
	};
}