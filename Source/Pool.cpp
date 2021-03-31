#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Pool.h"
#include "Map.h"

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
			bitmap.LoadBitmapA("RES\\pool\\fire_left_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 3:
		{
			bitmap.LoadBitmapA("RES\\pool\\fire_right_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 4:
		{
			bitmap.LoadBitmapA("RES\\pool\\water_left_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 5:
		{
			bitmap.LoadBitmapA("RES\\pool\\water_right_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 6:
		{
			bitmap.LoadBitmapA("RES\\pool\\toxic_left_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 7:
		{
			bitmap.LoadBitmapA("RES\\pool\\toxic_right_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 300:
		{
			bitmap.LoadBitmapA("RES\\pool\\fire_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 301:
		{
			bitmap.LoadBitmapA("RES\\pool\\water_0.bmp", RGB(255, 255, 255));
			break;
		}
		case 302:
		{
			bitmap.LoadBitmapA("RES\\pool\\toxic_0.bmp", RGB(255, 255, 255));
			break;
		}
		default:
			break;
		}
	}

	void Pool::OnShow()
	{
		bitmap_wall.SetTopLeft(x, y);//�Ȼ�ǽ�ڱ���
		bitmap_wall.ShowBitmap();
		bitmap.SetTopLeft(x, y - 16);//ͼƬ�߶���߰��
		bitmap.ShowBitmap();
	}

	void Pool::OnMove()
	{

	}

	void Pool::Interact(Map* m, bool is_boy, int direction)
	{
		if (type == 300 || type == 301 || type == 302)//ֻ�жϷ�б�淽��
		{
			if (direction == DIRECTION_DOWN)//ֻ�ж�����·����������Ϸ�
			{
				if (type == 300 && !is_boy)//fire & girl
				{
					m->PlayerDie(false);
				}
				else if (type == 301 && is_boy)//water & boy
				{
					m->PlayerDie(true);
				}
				else if (type == 302)//both
				{
					m->PlayerDie(is_boy);
				}
			}
		}
	}
}