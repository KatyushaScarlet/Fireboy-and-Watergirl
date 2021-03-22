#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Wall.h"

namespace game_framework
{
	Wall::Wall()
	{
		width = 1;
		height = 1;
		is_accessible = false;
	}
	void Wall::LoadItemBitmap()
	{
		bitmap.LoadBitmapA("RES\\wall.bmp");
	}
	void Wall::OnShow()
	{
		bitmap.SetTopLeft(y, x);
		bitmap.ShowBitmap();
	}

	//void Wall::SetTopLeft(int top, int left)
	//{
	//	x = left;
	//	y = top;
	//}
	//int  Wall::GetX1()
	//{
	//	return x;
	//}
	//int  Wall::GetY1()
	//{
	//	return y;
	//}
	//int  Wall::GetX2()
	//{
	//	return x + width;
	//}
	//int  Wall::GetY2()
	//{
	//	return y + height;
	//}
	//bool Wall::GetAccessible()
	//{
	//	return is_accessible;
	//}
	//bool Wall::GetVisibale()
	//{
	//	return is_visibale;
	//}
	//bool Wall::HitRectangle(int x1, int y1, int x2, int y2)
	//{
	//	return (GetX2() >= x1 && x <= x2 && GetY2() >= y1 && y <= y2);
	//}
}