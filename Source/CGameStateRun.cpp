#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "CGameStateRun.h"

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g), NUMBALLS(28)
	{
		//初始化对象
		map = new Map();

	}

	CGameStateRun::~CGameStateRun()
	{
		delete map;
	}

	void CGameStateRun::OnBeginState()
	{
		//从第一关开始
		//map_now_level = 0;
	}

	void CGameStateRun::OnMove()
	{
		map->OnMove();
	}

	void CGameStateRun::OnInit()
	{

		map->LoadBitmapMap();
		//map->InitMapLevel(0);

		////从第一关开始
		//map_now_level = 0;
	}

	const char KEY_LEFT = 37;
	const char KEY_UP = 38;
	const char KEY_RIGHT = 39;
	const char KEY_DOWN = 40;
	const char KEY_W = 87;
	const char KEY_A = 65;
	const char KEY_S = 83;
	const char KEY_D = 68;

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_UP:
			map->KeyDown(DIRECTION_UP, true);
			break;
		case KEY_LEFT:
			map->KeyDown(DIRECTION_LEFT, true);
			break;
		case KEY_DOWN:
			map->KeyDown(DIRECTION_DOWN, true);
			break;
		case KEY_RIGHT:
			map->KeyDown(DIRECTION_RIGHT, true);
			break;
		case KEY_W:
			map->KeyDown(DIRECTION_UP, false);
			break;
		case KEY_A:
			map->KeyDown(DIRECTION_LEFT, false);
			break;
		case KEY_S:
			map->KeyDown(DIRECTION_DOWN, false);
			break;
		case KEY_D:
			map->KeyDown(DIRECTION_RIGHT, false);
			break;
		default:
			break;
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_UP:
			map->KeyUp(DIRECTION_UP, true);
			break;
		case KEY_LEFT:
			map->KeyUp(DIRECTION_LEFT, true);
			break;
		case KEY_DOWN:
			map->KeyUp(DIRECTION_DOWN, true);
			break;
		case KEY_RIGHT:
			map->KeyUp(DIRECTION_RIGHT, true);
			break;
		case KEY_W:
			map->KeyUp(DIRECTION_UP, false);
			break;
		case KEY_A:
			map->KeyUp(DIRECTION_LEFT, false);
			break;
		case KEY_S:
			map->KeyUp(DIRECTION_DOWN, false);
			break;
		case KEY_D:
			map->KeyUp(DIRECTION_RIGHT, false);
			break;
		default:
			break;
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnShow()
	{
		map->OnShow();
	}
}