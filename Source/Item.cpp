#include "stdafx.h"

#include "Item.h"

namespace game_framework {

	void Item::SetTopLeft(int top, int left)
	{
		x = left;
		y = top;
	}
	int  Item::GetX1()
	{
		return x;
	}
	int  Item::GetY1()
	{
		return y;
	}
	int  Item::GetX2()
	{
		return x + width;
	}
	int  Item::GetY2()
	{
		return y + height;
	}
	bool Item::GetAccessible()
	{
		return is_accessible;
	}
	bool Item::GetVisibale()
	{
		return is_visibale;
	}
	bool Item::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = GetX2();
		int y2 = GetY2();
		
		if (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2) {
			TRACE("tx1:%d,ty1:%d,tx2:%d,ty2:%d - x1:%d,y1:%d,x2:%d,y2:%d\n", tx1/32, ty1/32, tx2, ty2,x1/32, y1/32, x2, y2);
		}
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
}