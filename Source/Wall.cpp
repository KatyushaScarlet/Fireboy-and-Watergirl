#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Wall.h"

namespace game_framework
{
	Wall::Wall()
	{
		type = 1;

		width = 32 - 1;
		height = 32 - 1;
		is_accessible = false;
	}
	void Wall::LoadItemBitmap()
	{
		bitmap.LoadBitmapA("RES\\wall.bmp");
	}
	void Wall::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}
	void Wall::OnMove()
	{

	}
	void Wall::Interact(Map* m, bool is_boy, int direction)
	{

	}
}