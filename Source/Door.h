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

		void AnimationStart();
		void AnimationReset();
	protected:
		CAnimation bitmap;
		void AddAnimationBitmap(string path);
	};
}