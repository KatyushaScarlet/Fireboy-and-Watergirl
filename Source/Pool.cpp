#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Pool.h"
#include "CGameStateRun.h"

namespace game_framework
{


	class Map;
	Pool::Pool(int type)
	{
		this->type = type;

		width = 32 - 1;
		height = 32 - 1;
		is_accessible = false;
	}

	void Pool::LoadItemBitmap()
	{
		bitmap_wall.LoadBitmapA("RES\\wall.bmp");

		switch (type)
		{
		case 2:
		{
			string path = "RES\\pool\\fire_left_";
			AddAnimationBitmap(path);
			break;
		}
		case 3:
		{
			string path = "RES\\pool\\fire_right_";
			AddAnimationBitmap(path);
			break;
		}
		case 4:
		{
			string path = "RES\\pool\\water_left_";
			AddAnimationBitmap(path);
			break;
		}
		case 5:
		{
			string path = "RES\\pool\\water_right_";
			AddAnimationBitmap(path);
			break;
		}
		case 6:
		{
			string path = "RES\\pool\\toxic_left_";
			AddAnimationBitmap(path);
			break;
		}
		case 7:
		{
			string path = "RES\\pool\\toxic_right_";
			AddAnimationBitmap(path);
			break;
		}
		case 300:
		{
			string path = "RES\\pool\\fire_";
			AddAnimationBitmap(path);
			break;
		}
		case 301:
		{
			string path = "RES\\pool\\water_";
			AddAnimationBitmap(path);
			break;
		}
		case 302:
		{
			string path = "RES\\pool\\toxic_";
			AddAnimationBitmap(path);
			break;
		}
		default:
			break;
		}
	}

	void Pool::OnShow()
	{
		bitmap_wall.SetTopLeft(x, y);//先画墙
		bitmap_wall.ShowBitmap();
		animation_pool.SetTopLeft(x, y - 16);//提高半格画水池
		animation_pool.OnShow();
	}

	void Pool::OnMove()
	{
		animation_pool.SetDelayCount(2); //設定速度
		animation_pool.OnMove();
	}

	void Pool::AddAnimationBitmap(string path)
	{
		string extension = ".bmp";
		for (int i = 0; i <= 14; i++) {
			string bitmapPath = path + to_string(i) + extension;
			char* p = (char*)bitmapPath.c_str();
			animation_pool.AddBitmap(p, RGB(255, 255, 255));
		}
	}
}