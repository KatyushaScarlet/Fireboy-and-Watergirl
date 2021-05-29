#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>

#include "CGameStateRun.h"

namespace game_framework
{
	const char KEY_LEFT = 37;
	const char KEY_UP = 38;
	const char KEY_RIGHT = 39;
	const char KEY_DOWN = 40;
	const char KEY_W = 87;
	const char KEY_A = 65;
	const char KEY_S = 83;
	const char KEY_D = 68;

	bool flag_pause;
	bool flag_gameover;

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (flag_game_loaded)
		{
			switch (nChar)
			{
			case KEY_UP:
				if (boy->GetVerticalState() == DIRECTION_NONE)
				{
					boy->SetVerticalState(DIRECTION_UP);
				}
				break;
				//case KEY_DOWN:

				//	break;
			case KEY_LEFT:
				if (boy->GetHorizontalState() == DIRECTION_NONE)
				{
					boy->SetHorizontalState(DIRECTION_LEFT);
				}
				break;
			case KEY_RIGHT:
				if (boy->GetHorizontalState() == DIRECTION_NONE)
				{
					boy->SetHorizontalState(DIRECTION_RIGHT);
				}
				break;
				/////////////////////////////////////////////////
			case KEY_W:
				if (girl->GetVerticalState() == DIRECTION_NONE)
				{
					girl->SetVerticalState(DIRECTION_UP);
				}
				break;
				//case KEY_S:

				//	break;
			case KEY_A:
				if (girl->GetHorizontalState() == DIRECTION_NONE)
				{
					girl->SetHorizontalState(DIRECTION_LEFT);
				}
				break;
			case KEY_D:
				if (girl->GetHorizontalState() == DIRECTION_NONE)
				{
					girl->SetHorizontalState(DIRECTION_RIGHT);
				}
				break;
			default:
				break;
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (flag_game_loaded)
		{
			switch (nChar)
			{
				//case KEY_UP:

				//	break;
				//case KEY_DOWN:

				//	break;
			case KEY_LEFT:
				if (boy->GetHorizontalState() == DIRECTION_LEFT)
				{
					boy->SetHorizontalState(DIRECTION_NONE);
				}
				break;
			case KEY_RIGHT:
				if (boy->GetHorizontalState() == DIRECTION_RIGHT)
				{
					boy->SetHorizontalState(DIRECTION_NONE);
				}
				break;
				//case KEY_W:

				//	break;
				//case KEY_S:

				//	break;
			case  KEY_A:
				if (girl->GetHorizontalState() == DIRECTION_LEFT)
				{
					girl->SetHorizontalState(DIRECTION_NONE);
				}
				break;
			case KEY_D:
				if (girl->GetHorizontalState() == DIRECTION_RIGHT)
				{
					girl->SetHorizontalState(DIRECTION_NONE);
				}
				break;
			default:
				break;
			}
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(true);
		//mouse_click = 1;
		//TRACE("mouse click\n");
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
		//mouse_x = point.x;
		//mouse_y = point.y;
		//TRACE("x=%d,y=%d\n", mouse_x, mouse_y);
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingRight(false);	
	}

}