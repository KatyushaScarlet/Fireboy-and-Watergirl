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
			break;
		}
		case 501://����
		{
			break;
		}
		default:
			break;
		}
	}

	void Switch::OnShow()
	{

	}

	void Switch::Interact(CGameStateRun* game, bool is_boy, int direction)
	{

	}

	void Switch::Bind(Platform* platform)
	{

	}
}