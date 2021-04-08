#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Diamond.h"
#include "CGameStateRun.h"

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
		switch (type)
		{
		case 200:
		{
			bitmap.LoadBitmapA("RES\\diamond\\fire.bmp", RGB(255, 255, 255));
			break;
		}
		case 201:
		{
			bitmap.LoadBitmapA("RES\\diamond\\water.bmp", RGB(255, 255, 255));
			break;
		}
		default:
			break;
		}
	}

	void Diamond::OnShow()
	{
		bitmap.SetTopLeft(x, y + 2);
		bitmap.ShowBitmap();
	}

	void Diamond::OnMove()
	{

	}

	void Diamond::Interact(CGameStateRun* game, bool is_boy, int direction)
	{
		if (type == 200 && is_boy)
		{
			game->AddScore(true);
			is_visibale = false;
		}
		else if (type == 201 && !is_boy)
		{
			game->AddScore(false);
			is_visibale = false;
		}
	}
}