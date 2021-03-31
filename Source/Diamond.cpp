#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Diamond.h"
#include "Map.h"

namespace game_framework
{
	class Map;
	Diamond::Diamond(int type)
	{
		this->type = type;

		width = 32 - 1;
		height = 32 - 1;
		is_accessible = true;
	}
	void Diamond::LoadItemBitmap()
	{
		if (type == 200)
		{
			bitmap.LoadBitmapA("RES\\diamond\\fire.bmp",RGB(255,255,255));
		}
		else if (type == 201)
		{
			bitmap.LoadBitmapA("RES\\diamond\\water.bmp", RGB(255, 255, 255));
		}
	}
	void Diamond::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}
	void Diamond::OnMove()
	{

	}
	void Diamond::Interact(Map* m, bool is_boy)
	{
		if (type == 200 && is_boy)
		{
			m->AddScore(true);
			is_visibale = false;
		}
		else if (type == 201 && !is_boy)
		{
			m->AddScore(false);
			is_visibale = false;
		}
	}
}