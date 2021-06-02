#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Box.h"
#include "CGameStateRun.h"

namespace game_framework
{
	Box::Box()
	{
		width = 64;
		height = 64;
		is_accessible = false;
	}

	void Box::LoadItemBitmap()
	{
		bitmap.LoadBitmapA("RES\\box\\box.bmp", RGB(255, 255, 255));
	}

	void Box::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Box::OnMove()
	{

	}
}