#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Door.h"
#include "CGameStateRun.h"

namespace game_framework
{
	Door::Door(int type)
	{
		this->type = type;

		width = 96 - 1;
		height = 96 - 1;
		is_accessible = true;
	}

	void Door::LoadItemBitmap()
	{
		switch (type)
		{
		case 400:
		{
			string path = "RES\\door\\FinishBoy";
			AddAnimationBitmap(path);
			break;
		}
		case 401:
		{
			string path = "RES\\door\\FinishGirl";
			AddAnimationBitmap(path);
			break;
		}
		default:
			break;
		}
	}

	void Door::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.OnShow();
	}

	void Door::OnMove()
	{
		
	}

	void Door::AddAnimationBitmap(string path)
	{
		string extension = ".bmp";
		for (int i = 0; i <= 14; i++) {
			string bitmapPath = path + to_string(i) + extension;
			char* p = (char*)bitmapPath.c_str();
			bitmap.AddBitmap(p, RGB(255, 255, 255));
		}
	}

	void Door::Interact(CGameStateRun* game, bool is_boy, int direction)
	{
		//获取玩家坐标
		PlayerCoordinate coordinate = game->GetPlayerCoordinate(is_boy);
		int x1 = coordinate.x1;
		int x2 = coordinate.x2;

		if ((x1 > this->GetX1()) && (x2 < this->GetX2()))//玩家完全进入门内
		{
			if (type == 400 && is_boy)
			{
				game->PlayerReachExit(true, true);
				bitmap.SetDelayCount(2); //設定速度
				bitmap.OnMove();
				//TRACE("boy reach exit\n");
			}
			else if (type == 401 && !is_boy)
			{
				game->PlayerReachExit(false, true);
				bitmap.SetDelayCount(2); //設定速度
				bitmap.OnMove();
				//TRACE("girl reach exit\n");
			}
		}
		else
		{
			if (type == 400 && is_boy)
			{
				game->PlayerReachExit(true, false);
				
				//TRACE("boy leave exit\n");
			}
			else if (type == 401 && !is_boy)
			{
				game->PlayerReachExit(false, false);
				//TRACE("girl leave exit\n");
			}
		}
	}
}