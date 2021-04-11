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
		this->x = x;
		this->y = y;
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
			bitmap_switch_on.LoadBitmapA("RES\\switch\\button_on.bmp", RGB(255, 255, 255));
			bitmap_switch_off.LoadBitmapA("RES\\switch\\button_off.bmp", RGB(255, 255, 255));
			break;
		}
		case 501://拉杆
		{
			bitmap_switch_on.LoadBitmapA("RES\\switch\\stick_on.bmp", RGB(255, 255, 255));
			bitmap_switch_off.LoadBitmapA("RES\\switch\\stick_off.bmp", RGB(255, 255, 255));
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

	void Switch::Interact(CGameStateRun* game, bool is_boy, int direction)
	{
		//获取玩家坐标
		PlayerCoordinate coordinate = game->GetPlayerCoordinate(is_boy);
		int x1 = coordinate.x1;
		int x2 = coordinate.x2;
		int y2 = coordinate.y2;

		switch (type)
		{
		case 500://按钮
		{
			if ((x1 > this->GetX1() - 16) && (x2 < this->GetX2() + 16) /*&& (y2 > this->GetY1())*/)//扩大判定范围
			{
				if (status == SWITCH_RELEASE)//按钮只能被按下一次
				{
					is_on = true;
					status = SWITCH_PRESS;
					//TRACE("player press\n");
				}
			}
			else
			{
				if (status == SWITCH_PRESS)//玩家离开后按钮被松开
				{
					is_on = false;
					status = SWITCH_RELEASE;
					//TRACE("player release\n");
				}
			}
			break;
		}
		case 501://拉杆
		{
			if ((x1 > this->GetX1() - 16) && (x2 < this->GetX2() + 16))//扩大判定范围
			{
				//if (status == SWITCH_RELEASE)//按钮只能被按下一次
				//{
				//	is_on = true;
				//	status = SWITCH_PRESS;
				//	//TRACE("player enter\n");
				//}
				if (status == SWITCH_RELEASE)
				{
					is_on = !is_on;//拉杆状态切换
					status == SWITCH_PRESS;
					TRACE("player enter\n");
				}
			}
			else
			{

			}

			//else 
			//{
			//	if ((x1 > this->GetX2() + 16) || (x2 < this->GetX1() - 16))//完全离开
			//	{
			//		if (status == SWITCH_PRESS)
			//		{

			//			status = SWITCH_RELEASE;
			//		}
			//	}
			//	//if (status == SWITCH_PRESS)//玩家离开后按钮被松开
			//	//{
			//	//	is_on = false;
			//	//	status = SWITCH_RELEASE;
			//	//	//TRACE("player exit\n");
			//	//}
			//}
			break;
		}
		default:
			break;
		}
	}

	void Switch::Bind(Platform* platform)
	{
		this->bind_platform = platform;
	}
}