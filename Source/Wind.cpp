#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Wind.h"

namespace game_framework
{
	Wind::Wind()
	{
		type = 600;

		width = 96;
		height = 32;
		is_accessible = false;
	}

	void Wind::LoadItemBitmap()
	{
		bitmap_wall.LoadBitmapA("RES\\wall.bmp");
		bitmap.LoadBitmapA("RES\\wind\\0.bmp",RGB(255,255,255));
	}

	void Wind::OnShow()
	{
		bitmap_wall.SetTopLeft(x, y);//œ»ª≠«Ω
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 32, y);//œ»ª≠«Ω
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 64, y);//œ»ª≠«Ω
		bitmap_wall.ShowBitmap();
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Wind::OnMove()
	{

	}
}