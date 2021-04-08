#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>

#include "CGameStateRun.h"

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		//InitMapLevel(0);
	}

	CGameStateRun::~CGameStateRun()
	{
		//Reset();
		ResetMap();
	}

	void CGameStateRun::ResetMap()
	{
		//game_stop = true;
			//delete boy;
			//delete girl;

		for each (Item * item in items)
		{
			delete item;
		}
		items.clear();
	}

	void CGameStateRun::OnBeginState()//游戏每次重开后载入
	{
		InitMapLevel(0);
	}

	void CGameStateRun::OnInit()//只在第一次启动时载入
	{
		LoadGameBitmap();
	}

	void CGameStateRun::LoadGameBitmap()//只执行一次
	{
		background.LoadBitmap("RES\\background.bmp");
	}

	void CGameStateRun::LoadItemBitmap()//更换关卡或重启后执行
	{
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();

		for each (Item * item in items)
		{
			item->LoadItemBitmap();
		}
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
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingRight(false);	
	}

	void CGameStateRun::OnShow()//显示
	{
		if (flag_game_loaded)
		{
			//加载背景
			background.SetTopLeft(0, 0);
			background.ShowBitmap();
			//显示物体
			for each (Wall * item in items)
			{
				if (item->is_visibale)
				{
					item->OnShow();
				}
			}
			//加载玩家
			boy->OnShow();
			girl->OnShow();
		}
	};

	void CGameStateRun::OnMove()//移动
	{
		if (flag_game_loaded)
		{
			boy->OnMove(this);
			girl->OnMove(this);
		}
	}

	bool CGameStateRun::CanMove(Player* player, int direction)//判定是否能移动
	{
		int x1, y1, x2, y2;
		bool accessible = true;
		bool is_boy = player->is_boy;
		x1 = player->GetX1();
		y1 = player->GetY1();
		x2 = player->GetX2();
		y2 = player->GetY2();
		//TRACE("ax1:%d,ay1:%d,ax2:%d,ay2:%d\n", x1, y1, x2, y2);
		for each (Item * item in items)
		{
			switch (direction)
			{
			case DIRECTION_UP:
				if (item->HitRectangle(x1, y1 - player->GetVelocity(), x2, y2 - player->GetVelocity()))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						item->Interact(this, is_boy, DIRECTION_UP);
					}
				}
				break;
			case DIRECTION_DOWN:
				if (item->HitRectangle(x1, y1 + player->GetVelocity(), x2, y2 + player->GetVelocity()))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						item->Interact(this, is_boy, DIRECTION_DOWN);
					}
				}
				break;
			case DIRECTION_LEFT:
				if (item->HitRectangle(x1 - player->GetStep(), y1, x2 - player->GetStep(), y2))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						item->Interact(this, is_boy, DIRECTION_LEFT);
					}
				}
				break;
			case DIRECTION_RIGHT:
				if (item->HitRectangle(x1 + player->GetStep(), y1, x2 + player->GetStep(), y2))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						item->Interact(this, is_boy, DIRECTION_RIGHT);
					}
				}
				break;
			default:
				break;
			}

			//jump out
			if (flag_change_level)
			{
				flag_change_level = false;
				accessible = false;
				break;
			}
		}

		return accessible;
	}

	void CGameStateRun::AddScore(bool is_boy)//玩家增加分数
	{
		if (is_boy)
		{
			score_boy++;
		}
		else
		{
			score_girl++;
		}
	}

	void CGameStateRun::PlayerDie(bool is_boy)//玩家死亡
	{
		if (is_boy)
		{
			boy->is_die = true;
			boy->is_visible = false;
			TRACE("boy die\n");
		}
		else
		{
			girl->is_die = true;
			girl->is_visible = false;
			TRACE("girl die\n");
		}
		//暂停游戏逻辑
		flag_game_loaded = false;
		//游戏结束
		GotoGameState(GAME_STATE_OVER);
	}

	void CGameStateRun::PlayerReachExit(bool is_boy, bool value)//玩家到达出口
	{
		if (is_boy)
		{
			boy->reach_exit = value;
		}
		else
		{
			girl->reach_exit = value;
		}
		//todo 到达出口后不可移动？
		//todo 两人均达到出口后，切换关卡?

		if (boy->reach_exit && girl->reach_exit)
		{
			boy->reach_exit = false;
			girl->reach_exit = false;
			//暂停游戏逻辑
			flag_game_loaded = false;
			//准备切换关卡
			flag_change_level = true;
			//todo 
			now_level++;
			InitMapLevel(now_level);
		}
	}

	void CGameStateRun::InitMapLevel(int level)//初始化地图数据 0~9
	{
		//停止游戏逻辑
		flag_game_loaded = false;
		//清空地图
		ResetMap();
		//设置目前关卡
		now_level = level;
		int map_level_0[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,400,0,0,401,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,201,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,100,101,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0,1,0},
			{1,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,6,302,302,302,7,1,1,1,0,0,0,0,1,0},
			{1,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,201,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,300,300,300,3,1,1,1,4,301,301,301,5,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

		//int map_level_0[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,400,0,0,401,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,201,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,100,101,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		//	{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0},
		//	{1,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,6,302,302,302,7,1,1,1,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,201,0,0,0,0,0,1,1,1,1,0},
		//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,300,300,300,3,1,1,1,4,301,301,301,5,1,1,1,1,1,1,1,0},
		//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		//};

		int map_level_1[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,400,0,0,401,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,200,0,0,201,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,1,1,1,6,302,302,302,302,302,302,7,1,1,1,1,1,1,6,302,302,302,302,302,302,7,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,201,0,0,0,0,200,0,0,0,0,0,0,0,0,201,0,0,0,200,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,201,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,200,0,0,0,200,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,4,301,301,301,301,301,301,301,5,0,0,0,0,0,0,0,2,300,300,300,300,300,300,300,3,0,0,0,0,0,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,200,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,201,0,0,0,201,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,2,300,300,300,300,300,300,300,3,1,1,1,1,1,1,1,4,301,301,301,301,301,301,301,5,1,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

		//int map_level_1[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,0,100,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//	{0,1,1,1,1,1,1,302,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		//};

		//地图赋值
		switch (level)
		{
		case 0:
		{
			for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
			{
				for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
				{
					map_array[i][j] = map_level_0[i][j];
				}
			}
			break;
		}
		case 1:
		{
			for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
			{
				for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
				{
					map_array[i][j] = map_level_1[i][j];
				}
			}
			break;
		}
		default:
			break;
		}

		//加载物件
		for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
		{
			for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
			{
				switch (map_array[i][j])
				{
				case 1:
				{

					Wall* wall = new Wall();
					wall->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(wall);
					if (level == 1)
					{
						TRACE("wall, x1=%d ,y1=%d ,x2=%d ,y2%d \n", wall->GetX1(), wall->GetY1(), wall->GetX2(), wall->GetY2());
					}
					break;
				}
				case 2:
				{
					Pool* fire_pool = new Pool(2);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(fire_pool);
					break;
				}
				case 3:
				{
					Pool* fire_pool = new Pool(3);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(fire_pool);
					break;
				}
				case 4:
				{
					Pool* water_pool = new Pool(4);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(water_pool);
					break;
				}
				case 5:
				{
					Pool* water_pool = new Pool(5);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(water_pool);
					break;
				}
				case 6:
				{
					Pool* toxic_pool = new Pool(6);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(toxic_pool);
					break;
				}
				case 7:
				{
					Pool* toxic_pool = new Pool(7);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(toxic_pool);
					break;
				}
				case 100:
				{
					boy = make_unique<Player>(true);
					boy->SetTopLeft(i * MAP_GIRD_PIXEL, j * MAP_GIRD_PIXEL);
					break;
				}
				case 101:
				{
					girl = make_unique<Player>(false);
					girl->SetTopLeft(i * MAP_GIRD_PIXEL, j * MAP_GIRD_PIXEL);
					break;
				}
				case 200:
				{
					Diamond* fire_diamond = new Diamond(200);
					fire_diamond->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(fire_diamond);
					break;
				}
				case 201:
				{
					Diamond* water_diamond = new Diamond(201);
					water_diamond->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(water_diamond);
					break;
				}
				case 300:
				{
					Pool* fire_pool = new Pool(300);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(fire_pool);
					break;
				}
				case 301:
				{
					Pool* water_pool = new Pool(301);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(water_pool);
					break;
				}
				case 302:
				{
					Pool* toxic_pool = new Pool(302);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(toxic_pool);
					break;
				}
				case 400:
				{
					Door* fire_door = new Door(400);
					fire_door->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					items.push_back(fire_door);
					break;
				}
				case 401:
				{
					Door* water_door = new Door(401);
					water_door->SetTopLeft(MAP_GIRD_PIXEL* i, MAP_GIRD_PIXEL* j);
					items.push_back(water_door);
					break;
				}
				default:
					break;
				}
			}
		}

		LoadItemBitmap();
		//继续游戏逻辑
		flag_game_loaded = true;
	}

	PlayerCoordinate CGameStateRun::GetPlayerCoordinate(bool is_boy)
	{
		PlayerCoordinate coordinate;
		if (is_boy)
		{
			coordinate.x1 = boy->GetX1();
			coordinate.y1 = boy->GetY1();
			coordinate.x2 = boy->GetX2();
			coordinate.y2 = boy->GetY2();
		}
		else
		{
			coordinate.x1 = girl->GetX1();
			coordinate.y1 = girl->GetY1();
			coordinate.x2 = girl->GetX2();
			coordinate.y2 = girl->GetY2();
		}

		return coordinate;
	}
}
