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
