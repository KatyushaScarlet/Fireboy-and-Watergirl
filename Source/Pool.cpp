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

	}
	void Pool::OnShow()
	{
		bitmap.SetTopLeft(x, y);
		bitmap.ShowBitmap();
	}
	void Pool::OnMove()
	{

	}
	void Pool::Interact(Map* m, bool is_boy)
	{

	}
}