#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Platform.h"
#include "CGameStateRun.h"

namespace game_framework
{
	Platform::Platform(int type, int init_1_x, int init_1_y, int init_2_x, int init_2_y)
	{
		this->init_1_x = init_1_x;
		this->init_1_y = init_1_y;
		this->init_2_x = init_2_x;
		this->init_2_y = init_2_y;

		this->x = init_1_x;
		this->y = init_1_y;
		this->type = type;

		is_accessible = false;

		switch (type)
		{
		case 502://水平
		{
			width = 32 * 4;
			height = 32;
			break;
		}
		case 504://垂直
		{
			width = 32;
			height = 32 * 4;
			break;
		}
		default:
			break;
		}
	}
	void Platform::LoadItemBitmap()
	{
		switch (type)
		{
		case 502://水平
		{
			bitmap.LoadBitmapA("RES\\platform\\horizon.bmp");
			break;
		}
		case 504://垂直
		{
			bitmap.LoadBitmapA("RES\\platform\\vertical.bmp");
			break;
		}
		default:
			break;
		}
	}
	void Platform::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}
	void Platform::Interact(CGameStateRun* game, bool is_boy, int direction)
	{

	}
	void Platform::Trigger(bool is_on)
	{
		if (is_on)
		{
			x = this->init_1_x;
			y = this->init_1_y;
		}
		else
		{
			x = this->init_2_x;
			y = this->init_2_y;
		}
	}
}