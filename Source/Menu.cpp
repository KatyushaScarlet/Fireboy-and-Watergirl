#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Menu.h"

namespace game_framework
{
	Menu::Menu()
	{

	}

	void Menu::LoadItemBitmap()
	{
		bitmap_pause0.LoadBitmapA("RES\\menu\\pause0.bmp");
		bitmap_pause1.LoadBitmapA("RES\\menu\\pause1.bmp");
		bitmap_over.LoadBitmapA("RES\\menu\\over.bmp");
	}

	void Menu::OnShow(int menuType)
	{
		switch (menuType)
		{
		case 0:
			bitmap_pause0.SetTopLeft(left, top);
			bitmap_pause0.ShowBitmap();
			break;
		case 1:
			bitmap_pause1.SetTopLeft(left,top);
			bitmap_pause1.ShowBitmap();
			break;
		case 2:
			bitmap_over.SetTopLeft(left, top);
			bitmap_over.ShowBitmap();
			break;
		default:
			break;
		}
	}

	void Menu::OnMove(int menuType)
	{

	}
}