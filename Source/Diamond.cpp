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
	Diamond::Diamond(int type)
	{
		this->type = type;

		width = 32 ;
		height = 64 ;//钻石高度增加
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
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Diamond::OnMove()
	{

	}
}