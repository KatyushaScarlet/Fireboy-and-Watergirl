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
		width = 1;
		height = 1;
		is_accessible = false;
	}
	void Wall::LoadItemBitmap()
	{
		bitmap.LoadBitmapA("RES\\wall.bmp");
	}
	void Wall::OnShow()
	{
		bitmap.SetTopLeft(y, x);
		bitmap.ShowBitmap();
	}
}