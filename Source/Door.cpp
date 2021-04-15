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

		//设定初始动画
		bitmap_ptr = &bitmap_open;
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
		bitmap_ptr->SetTopLeft(x, y);
		bitmap_ptr->OnShow();
	}

	void Door::OnMove()
	{
		if (anime_play)//如果动画在播放中
		{
			if (!bitmap_ptr->IsFinalBitmap())//如果没有播放到最后一张
			{
				if (anime_open)//判断动画类型
				{
					bitmap_ptr = &bitmap_open;//开门动画
				}
				else
				{

					bitmap_ptr = &bitmap_close;//关门动画
				}

				bitmap_ptr->SetDelayCount(2);
				bitmap_ptr->OnMove();//继续切换动画
			}
			else
			{
				anime_play = false;//停止播放
				if (anime_open)//判断刚才结束的动画类型
				{
					bitmap_ptr = &bitmap_close;//开门动画结束，则切换到关门动画
				}
				else
				{
					bitmap_ptr = &bitmap_open;//关门动画结束，则切换到开门动画
				}
				bitmap_ptr->Reset();//重置动画
			}
		}
	}

	void Door::AddAnimationBitmap(string path)
	{
		string extension = ".bmp";
		string bitmapPath = "";

		for (int i = 0; i <= 21; i++) {
			bitmapPath = path + to_string(i) + extension;
			char* ptr1 = (char*)bitmapPath.c_str();
			bitmap_open.AddBitmap(ptr1, RGB(255, 255, 255));

			bitmapPath = path + to_string(21-i) + extension;
			char* ptr2 = (char*)bitmapPath.c_str();
			bitmap_close.AddBitmap(ptr2, RGB(255, 255, 255));
		}
	}

	void Door::AnimationOpenDoor()
	{
		//仅被触发一次
		TRACE("door open\n");
		if (!anime_play)//如果动画未开始播放
		{
			anime_open = true;//切换到开门动画
			anime_play = true;//开始播放
		}
	}

	void Door::AnimationCloseDoor()
	{
		//仅被触发一次
		TRACE("door close\n");
		if (!anime_play)//如果动画未开始播放
		{
			anime_open = false;//切换到关门动画
			anime_play = true;//开始播放
		}
	}
}