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
		return is_accessible;
	}
	bool Item::HitRectangle(int x1, int y1, int x2, int y2)
	{
		return (GetX2() >= x1 && x <= x2 && GetY2() >= y1 && y <= y2);
	}
}