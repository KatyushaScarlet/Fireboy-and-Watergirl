#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>

#include "CGameStateRun.h"

//#define PLAYER_GIRD_PIXEL 32
//#define PLAYER_STEP_PIXEL 4
//#define INITIAL_VELOCITY 16

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		//InitMapLevel(0);
	}

	CGameStateRun::~CGameStateRun()
	{
		ResetMap();
	}

	void CGameStateRun::ResetMap()
	{
		//for each (Item * item in items)
		//{
		//	delete item;
		//}
		//items.clear();
		item_ptrs.clear();
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

		for each (shared_ptr<Item> item in item_ptrs)
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
			for each (shared_ptr<Item> item in item_ptrs)
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
			MovePlayer(boy);
			MovePlayer(girl);
			boy->OnMove();
			girl->OnMove();

			for each (shared_ptr<Item> item in item_ptrs)
			{
				if (item->is_visibale)
				{
					item->OnMove();
				}
			}
		}
	}

	void CGameStateRun::MovePlayer(shared_ptr<Player> player)//移动
	{
		bool can_move;

		if (player->moving_vertical == DIRECTION_UP)
		{
			can_move = CanMove(player, DIRECTION_UP);
			//上升状态
			//TRACE("up\n");
			if (can_move && player->velocity > 0)//如果上方可通行，垂直速度大于0
			{
				player->SetAni(player->GetUp());
				player->y -= player->velocity;
				player->velocity--;
			}
			else
			{
				player->moving_vertical = DIRECTION_DOWN;//当速度<=0时，垂直方向变为下降
				player->velocity = 1;
				player->SetAni(player->GetDown());
			}
		}
		else
		{
			//如果非上升状态，始终判断是否下落
			//TRACE("down\n");
			can_move = CanMove(player, DIRECTION_DOWN);
			if (can_move)//如果下方可通行
			{
				player->moving_vertical = DIRECTION_DOWN;
				player->y += player->velocity;
				player->SetAni(player->GetDown());
				if (player->velocity < 5)//防止下落速度过大
				{
					player->velocity++;
				}
				else
				{
					player->velocity = 4;//fixbug:当直接掉下时初速度为 INITIAL_VELOCITY （跳起初始速度） 而不是1（掉落初始速度）
				}
			}
			else
			{
				player->moving_vertical = DIRECTION_NONE;//当下方不可通行时，垂直方向变成静止
				player->velocity = INITIAL_VELOCITY;//加速度变为初始值
				player->SetAni(player->GetStatic());
			}
		}

		switch (player->moving_horizontal)//水平移动
		{

		case DIRECTION_LEFT:
			can_move = CanMove(player, DIRECTION_LEFT);
			if (can_move) {
				player->x -= PLAYER_STEP_PIXEL;
				player->SetAni(player->GetLeft());
			}
			break;
		case DIRECTION_RIGHT: {
			can_move = CanMove(player, DIRECTION_RIGHT);
			if (can_move) {
				player->x += PLAYER_STEP_PIXEL;
				player->SetAni(player->GetRight());
			}

			break;
		}
		case DIRECTION_NONE:
			break;
		default:
			break;
		}
	}

	bool CGameStateRun::CanMove(shared_ptr<Player> player, int direction)//判定是否能移动
	{
		int x1, y1, x2, y2;
		bool accessible = true;
		bool is_boy = player->is_boy;
		x1 = player->GetX1();
		y1 = player->GetY1();
		x2 = player->GetX2();
		y2 = player->GetY2();
		//TRACE("ax1:%d,ay1:%d,ax2:%d,ay2:%d\n", x1, y1, x2, y2);
		for each (shared_ptr<Item> item in item_ptrs)
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

		if (boy->reach_exit && girl->reach_exit)
		{
			boy->reach_exit = false;
			girl->reach_exit = false;
			//暂停游戏逻辑
			flag_game_loaded = false;
			//准备切换关卡
			flag_change_level = true;
			//切换关卡
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
			{1,0,201,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,100,101,0,0,0,0,0,0,0,1,0},
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
			{1,0,101/*0*/,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,201,0,0,0,0,0,1,1,1,1,0},
			{1,0,100/*0*/,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,300,300,300,3,1,1,1,4,301,301,301,5,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

		int map_level_1[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,400,0,0,401,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100,101,0,0,0,0,0,0,0,1,0},
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
			{1,0,100/*0*/,0,101/*0*/,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,2,300,300,300,300,300,300,300,3,1,1,1,1,1,1,1,4,301,301,301,301,301,301,301,5,1,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

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

			//添加机关
			
			//platform1
			shared_ptr<Platform> platform1 = make_shared<Platform>(502, 1, 15, 1, 18);
			item_ptrs.push_back(platform1);
			shared_ptr<Switch> platform1_stick = make_shared<Switch>(501, 9, 19);
			platform1_stick->Bind(platform1);//绑定平台
			item_ptrs.push_back(platform1_stick);

			//platform2
			shared_ptr<Platform> platform2 = make_shared<Platform>(502, 34, 12, 34, 15);
			item_ptrs.push_back(platform2);
			shared_ptr<Switch> platform2_button1 = make_shared<Switch>(500, 10, 14);
			shared_ptr<Switch> platform2_button2 = make_shared<Switch>(500, 30, 10);
			platform2_button1->Bind(platform2);//绑定平台
			platform2_button2->Bind(platform2);//绑定平台
			item_ptrs.push_back(platform2_button1);
			item_ptrs.push_back(platform2_button2);

			//platform3
			shared_ptr<Platform> platform3 = make_shared<Platform>(502, 50, 50, 6, 7);
			item_ptrs.push_back(platform3);
			shared_ptr<Switch> platform3_stick = make_shared<Switch>(501, 1, 6);
			platform3_stick->Bind(platform3);//绑定平台
			item_ptrs.push_back(platform3_stick);

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

			//添加机关

			//platform1
			shared_ptr<Platform> platform1 = make_shared<Platform>(503, 50, 50, 19, 10);
			item_ptrs.push_back(platform1);
			shared_ptr<Switch> platform1_button1 = make_shared<Switch>(500, 5, 19);
			shared_ptr<Switch> platform1_button2 = make_shared<Switch>(500, 33, 19);
			platform1_button1->Bind(platform1);//绑定平台
			platform1_button2->Bind(platform1);//绑定平台
			item_ptrs.push_back(platform1_button1);
			item_ptrs.push_back(platform1_button2);

			//platform2
			shared_ptr<Platform> platform2 = make_shared<Platform>(502, 17, 1, 17, 5);
			item_ptrs.push_back(platform2);
			shared_ptr<Switch> platform2_button1 = make_shared<Switch>(500, 12, 4);
			shared_ptr<Switch> platform2_button2 = make_shared<Switch>(500, 26, 4);
			platform2_button1->Bind(platform2);//绑定平台
			platform2_button2->Bind(platform2);//绑定平台
			item_ptrs.push_back(platform2_button1);
			item_ptrs.push_back(platform2_button2);

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

					//Wall* wall = new Wall();
					shared_ptr<Item> wall = make_shared<Wall>();
					wall->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(wall);
					break;
				}
				case 2:
				{
					shared_ptr<Item> fire_pool = make_shared<Pool>(2);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_pool);
					break;
				}
				case 3:
				{
					shared_ptr<Item> fire_pool = make_shared<Pool>(3);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_pool);
					break;
				}
				case 4:
				{
					shared_ptr<Item>  water_pool = make_shared<Pool>(4);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_pool);
					break;
				}
				case 5:
				{
					shared_ptr<Item> water_pool = make_shared<Pool>(5);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_pool);
					break;
				}
				case 6:
				{
					shared_ptr<Item> toxic_pool = make_shared<Pool>(6);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(toxic_pool);
					break;
				}
				case 7:
				{
					shared_ptr<Item> toxic_pool = make_shared<Pool>(7);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(toxic_pool);
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
					shared_ptr<Item> fire_diamond = make_shared<Diamond>(200);
					fire_diamond->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_diamond);
					break;
				}
				case 201:
				{
					shared_ptr<Item>  water_diamond = make_shared<Diamond>(201);
					water_diamond->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_diamond);
					break;
				}
				case 300:
				{
					//shared_ptr<Item> fire_pool = make_shared<Pool>(300);
					shared_ptr<Item> fire_pool = make_shared<Pool>(300);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_pool);
					break;
				}
				case 301:
				{
					//shared_ptr<Item> water_pool = make_shared<Pool>(301);
					shared_ptr<Item> water_pool = make_shared<Pool>(301);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_pool);
					break;
				}
				case 302:
				{
					//shared_ptr<Item> toxic_pool = make_shared<Pool>(302);
					shared_ptr<Item> toxic_pool = make_shared<Pool>(302);
					toxic_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(toxic_pool);
					break;
				}
				case 400:
				{
					shared_ptr<Item> fire_door = make_shared<Door>(400);
					fire_door->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_door);
					break;
				}
				case 401:
				{
					shared_ptr<Item> water_door = make_shared<Door>(401);
					water_door->SetTopLeft(MAP_GIRD_PIXEL* i, MAP_GIRD_PIXEL* j);
					item_ptrs.push_back(water_door);
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
