#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Tips.h"
#include "CGameStateRun.h"

namespace game_framework
{
	Tips::Tips(string name,int x,int y)
	{
		this->x = x * MAP_GIRD_PIXEL;
		this->y = y * MAP_GIRD_PIXEL;
		this->type = 1000;

		this->name = name;

		width = 0;
		height = 0;
		is_accessible = true;
	}

	void Tips::LoadItemBitmap()
	{
		string path = "RES\\tips\\" + name + ".bmp";
		char* p = (char*)path.c_str();

		bitmap.LoadBitmapA(p, RGB(0, 0, 0));
	}

	void Tips::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}

	void Tips::OnMove()
	{

	}
}