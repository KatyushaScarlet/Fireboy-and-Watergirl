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
		//ÿ�����붼�����
	}

	void CGameStatePause::OnInit()
	{
		//ֻ����һ��
		game_menu = make_shared<Menu>();
		game_menu->LoadItemBitmap();
	}

	void CGameStatePause::OnLButtonDown(UINT nFlags, CPoint point)  // ̎����Ą���
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
				//�ؿ�����
				flag_now_level = 0;
				//��������
				score_boy = 0;
				score_girl = 0;
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

	void CGameStatePause::OnLButtonUp(UINT nFlags, CPoint point)	// ̎����Ą���
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStatePause::OnMouseMove(UINT nFlags, CPoint point)	// ̎����Ą���
	{
		// �]�¡������Ҫ̎�����Ƅӵ�Ԓ����code���@�e
		mouse_x = point.x;
		mouse_y = point.y;
		//TRACE("x=%d,y=%d\n", mouse_x, mouse_y);
	}

	void CGameStatePause::OnRButtonDown(UINT nFlags, CPoint point)  // ̎����Ą���
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStatePause::OnRButtonUp(UINT nFlags, CPoint point)	// ̎����Ą���
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