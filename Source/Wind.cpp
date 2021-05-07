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
		bitmap.AddBitmap("RES\\wind\\0.bmp",RGB(255,255,255));
		bitmap.AddBitmap("RES\\wind\\1.bmp", RGB(255, 255, 255));
		bitmap.AddBitmap("RES\\wind\\2.bmp", RGB(255, 255, 255));
		bitmap.AddBitmap("RES\\wind\\3.bmp", RGB(255, 255, 255));
		string path = "RES\\wind_effect\\wind_effect00";
		string extension = ".bmp";
		for (int i = 0; i <= 29; i++) {
			string bitmapPath = path + to_string(i) + extension;
			char* p = (char*)bitmapPath.c_str();
			bitmap_wind.AddBitmap(p, RGB(0, 0, 0));
		}
	}

	void Wind::OnShow()
	{
		bitmap_wall.SetTopLeft(x, y);//先畫牆
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 32, y);//先畫牆
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 64, y);//先畫牆
		bitmap_wall.ShowBitmap();
		bitmap.SetTopLeft(x, y);
		bitmap.OnShow();
		bitmap.SetDelayCount(1);
		bitmap_wind.SetDelayCount(1);
		bitmap_wind.SetTopLeft(x, y-192);
		bitmap_wind.OnShow();
	}

	void Wind::OnMove()
	{
		bitmap.OnMove();
		bitmap_wind.OnMove();
	}


}