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
		for (int i = 0; i <= 21; i++) {
			string bitmapPath = path + to_string(i) + extension;
			char* p = (char*)bitmapPath.c_str();
			bitmap.AddBitmap(p, RGB(255, 255, 255));
		}
	}

	void Door::AnimationStart()
	{
		bitmap.SetDelayCount(2); //設定速度
		if (!bitmap.IsFinalBitmap()) 
		{
			bitmap.OnMove();
		}
	}
	void Door::AnimationReset()
	{
		bitmap.Reset();
	}
}