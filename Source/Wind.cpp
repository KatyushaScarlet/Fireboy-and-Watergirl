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
	}

	void Wind::OnShow()
	{
		bitmap_wall.SetTopLeft(x, y);//�Ȼ�ǽ
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 32, y);//�Ȼ�ǽ
		bitmap_wall.ShowBitmap();
		bitmap_wall.SetTopLeft(x + 64, y);//�Ȼ�ǽ
		bitmap_wall.ShowBitmap();
		bitmap.SetTopLeft(x, y);
		bitmap.OnShow();
		bitmap.SetDelayCount(1);
	}

	void Wind::OnMove()
	{
		bitmap.OnMove();
	}
}