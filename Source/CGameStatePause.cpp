#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include<memory>

#include "CGameStatePause.h"
#include "Menu.h"


namespace game_framework
{
	CGameStatePause::CGameStatePause(CGame* g)
		: CGameState(g)
	{

	}
	CGameStatePause::~CGameStatePause()
	{

	}

	void CGameStatePause::OnBeginState()
	{
		//每次载入都会加载
	}

	void CGameStatePause::OnInit()
	{
		//只加载一次
		game_menu = make_shared<Menu>();
		game_menu->LoadItemBitmap();
	}

	void CGameStatePause::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(true);



		//TRACE("mouse click\n");


		switch (flag_game_menu_type)
		{
		case 1:
			//pause
			GotoGameState(GAME_STATE_RUN);
			break;
		case 2:
			//over
			if (mouse_x<640)
			{
				//menu
				GotoGameState(GAME_STATE_OVER);
				//关卡清零
				flag_now_level = 0;
			}
			else
			{
				//retry
				GotoGameState(GAME_STATE_RUN);
			}
			break;
		default:
			break;
		}
	}

	void CGameStatePause::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStatePause::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
		mouse_x = point.x;
		mouse_y = point.y;
		TRACE("x=%d,y=%d\n", mouse_x, mouse_y);
	}

	void CGameStatePause::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStatePause::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingRight(false);	
	}

	void CGameStatePause::OnKeyDown(UINT, UINT, UINT)
	{
	}
	void CGameStatePause::OnKeyUp(UINT, UINT, UINT)
	{
	}
	void CGameStatePause::OnMove()
	{
	}
	void CGameStatePause::OnShow()
	{
		int type = flag_game_menu_type;
		game_menu->OnShow(type);
	}
}