#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "CGameStateRun.h"

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		InitMapLevel(0);

	}

	CGameStateRun::~CGameStateRun()
	{
		delete boy;
		delete girl;

		for each (Item * item in items)
		{
			delete item;
		}
	}

	void CGameStateRun::OnBeginState()
	{
		//从第一关开始
		//map_now_level = 0;
	}

	void CGameStateRun::OnInit()
	{

		background.LoadBitmap("RES\\background.bmp");
		for each (Item * item in items)
		{
			item->LoadItemBitmap();
		}
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();
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

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
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
		case  KEY_A :
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
	};

	void CGameStateRun::OnMove()//移动
	{
		boy->OnMove(this);
		girl->OnMove(this);
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
		//todo 游戏结束
	}

	void CGameStateRun::PlayerReachExit(bool is_boy)//玩家到达出口
	{
		if (is_boy)
		{
			boy->reach_exit = true;
		}
		else
		{
			girl->reach_exit = true;
		}
		//todo 到达出口后不可移动
		//todo 两人均达到出口后，切换关卡
	}

	void CGameStateRun::InitMapLevel(int level)//初始化地图数据 0~9
	{
		now_level = level;

		int map_level_0[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,201,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
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
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};

		int map_level_1[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,200,0,201,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,1,1,6,302,302,302,302,302,302,302,7,1,1,1,1,1,6,302,302,302,302,302,302,7,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,201,0,0,0,0,200,0,0,0,0,0,0,0,201,0,0,0,0,200,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,201,0,0,0,201,0,0,0,0,0,0,0,0,0,0,0,200,0,0,200,0,0,0,0,0,0,0,0,1,1,1,0},
			{1,0,0,0,0,0,4,101,101,101,0,101,101,101,5,0,0,0,0,0,0,0,2,300,300,300,300,300,300,3,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,101,0,0,0,200,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,201,0,0,201,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,2,300,1,300,300,300,300,300,3,1,1,1,1,1,1,1,4,101,101,101,101,101,101,5,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};

		//地图赋值
		switch (level)
		{
		case 0:
			for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
			{
				for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
				{
					map_array[i][j] = map_level_0[i][j];
				}
			}
			break;
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
					boy = new Player(true);
					boy->SetTopLeft(i * MAP_GIRD_PIXEL, j * MAP_GIRD_PIXEL);
					break;
				}
				case 101:
				{
					girl = new Player(false);
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
				default:
					break;
				}
			}
		}
	}
}
