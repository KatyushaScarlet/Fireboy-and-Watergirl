#pragma once

#include"Item.h"

namespace game_framework {

	enum DOOR_STATUS
	{
		//DOOR_DEFAULT,
		DOOR_ENTER,
		DOOR_LEAVE
	};


	class CMovingBitmap;
	class Door : public Item
	{
	public:
		Door(int type);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();

		//void AnimationStart();
		//void AnimationReset();

		void AnimationOpenDoor();
		void AnimationCloseDoor();

		int status = DOOR_LEAVE;
	private:
		//CAnimation bitmap;
		void AddAnimationBitmap(string path);

		CAnimation* bitmap_ptr;
		CAnimation bitmap_open;
		CAnimation bitmap_close;

		bool anime_play = false;
		bool anime_open = true;
	};
}