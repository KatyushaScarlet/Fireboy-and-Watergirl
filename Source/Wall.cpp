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
		width = 32;
		height = 32;
		is_accessible = false;
		test_flag = false;
	}
	void Wall::LoadItemBitmap()
	{
		bitmap.LoadBitmapA("RES\\wall.bmp");
		//for test
		test_bitmap.LoadBitmapA("RES\\player\\test.bmp");
	}
	void Wall::OnShow()
	{
		if (test_flag)
		{
			//for test
			test_bitmap.SetTopLeft(x, y);
			test_bitmap.ShowBitmap();
		}
		else
		{
			bitmap.SetTopLeft(x, y);
			bitmap.ShowBitmap();
		}
	}
	void Wall::OnMove()
	{
		//none
	}
	bool Wall::Interact()
	{
		//for test
		test_flag = true;
		return 0;
	}
}