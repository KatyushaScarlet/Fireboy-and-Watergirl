#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Door : public Item
	{
	public:
		Door(int type);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
	protected:
		CAnimation bitmap;
		void AddAnimationBitmap(string path);
	};
}