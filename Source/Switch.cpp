#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Switch.h"
#include "CGameStateRun.h"

namespace game_framework
{
	Switch::Switch(int type, int x, int y)
	{
		this->x = x * MAP_GIRD_PIXEL;
		this->y = y * MAP_GIRD_PIXEL;
		this->type = type;

		width = 32;
		height = 32;
		is_accessible = true;
	}

	void Switch::LoadItemBitmap()
	{
		switch (type)
		{
		case 500://按钮
		{
			bitmap_switch_on.LoadBitmapA("RES\\switch\\button_on.bmp", RGB(0, 0, 0));
			bitmap_switch_off.LoadBitmapA("RES\\switch\\button_off.bmp", RGB(0, 0, 0));
			break;
		}
		case 501://拉杆
		{
			bitmap_switch_on.LoadBitmapA("RES\\switch\\stick_on.bmp", RGB(0, 0, 0));
			bitmap_switch_off.LoadBitmapA("RES\\switch\\stick_off.bmp", RGB(0, 0, 0));
			break;
		}
		default:
			break;
		}
	}

	void Switch::OnShow()
	{
		if (is_on)
		{
			bitmap_switch_on.SetTopLeft(x, y);
			bitmap_switch_on.ShowBitmap();
		}
		else
		{
			bitmap_switch_off.SetTopLeft(x, y);
			bitmap_switch_off.ShowBitmap();
		}
	}

	void Switch::OnMove()
	{

	}

	void Switch::Bind(shared_ptr<Platform> platform)
	{
		this->bind_platform = platform;
	}

	void Switch::Trigger()
	{
		//触发平台
		bind_platform->Trigger(is_on);
	}
}