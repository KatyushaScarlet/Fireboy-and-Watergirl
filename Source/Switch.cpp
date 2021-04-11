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
		case 500://��ť
		{
			bitmap_switch_on.LoadBitmapA("RES\\switch\\button_on.bmp", RGB(255, 255, 255));
			bitmap_switch_off.LoadBitmapA("RES\\switch\\button_off.bmp", RGB(255, 255, 255));
			break;
		}
		case 501://����
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
		//��ȡ�������
		PlayerCoordinate coordinate = game->GetPlayerCoordinate(is_boy);
		int x1 = coordinate.x1;
		int x2 = coordinate.x2;
		int y2 = coordinate.y2;

		switch (type)
		{
		case 500://��ť
		{
			if ((x1 > this->GetX1() - 16) && (x2 < this->GetX2() + 16) /*&& (y2 > this->GetY1())*/)//�����ж���Χ
			{
				if (status == SWITCH_RELEASE)//��ťֻ�ܱ�����һ��
				{
					is_on = true;
					status = SWITCH_PRESS;
					//TRACE("player press\n");
				}
			}
			else
			{
				if (status == SWITCH_PRESS)//����뿪��ť���ɿ�
				{
					is_on = false;
					status = SWITCH_RELEASE;
					//TRACE("player release\n");
				}
			}
			break;
		}
		case 501://����
		{
			if ((x1 > this->GetX1() - 16) && (x2 < this->GetX2() + 16) /*&& (y2 > this->GetY1())*/)//�����ж���Χ
			{
				if (status == SWITCH_RELEASE)//���˱�������ת��״̬
				{
					is_on = !is_on;
					status = SWITCH_PRESS;
					//TRACE("player press\n");
				}
			}
			else
			{
				if (status == SWITCH_PRESS)//����뿪�󣬲��ɿ�
				{
					status = SWITCH_RELEASE;
					//TRACE("player release\n");
				}
			}
			break;
		}
		default:
			break;
		}
		
		//����ƽ̨
		//bind_platform->Trigger(is_on);
	}

	void Switch::Bind(Platform* platform)
	{
		this->bind_platform = platform;
	}
}