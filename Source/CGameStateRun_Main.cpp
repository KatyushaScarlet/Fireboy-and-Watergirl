#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>
#include <windows.h>

#include "CGameStateRun.h"

namespace game_framework
{
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
		item_ptrs.clear();
		//CAudio::Instance()->Stop(AUDIO_ADV);
		CAudio::Instance()->Stop(AUDIO_DIE);
		CAudio::Instance()->Stop(AUDIO_DIAMOND);
	}

	void CGameStateRun::OnBeginState()//游戏每次重开后载入
	{
		InitMapLevel(flag_now_level);//继续之前的关卡
	}

	void CGameStateRun::OnInit()//只在第一次启动时载入
	{
		LoadGameBitmap();
		CAudio::Instance()->Load(AUDIO_ADV, "sounds\\adv_sound.mp3");
		CAudio::Instance()->Load(AUDIO_DIE, "sounds\\die.mp3");
		CAudio::Instance()->Load(AUDIO_DIAMOND, "sounds\\911_Diamond_Sound.mp3");
		CAudio::Instance()->Load(AUDIO_GIRLJUMP, "sounds\\904_Jump1_Sound.wav");
		CAudio::Instance()->Load(AUDIO_BOYJUMP, "sounds\\901_Jump2_Sound.wav");
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\WaterSteps.mp3");
		CAudio::Instance()->Load(AUDIO_DOOR, "sounds\\906_Door_Sound.wav");

		score_boy = 0;
		score_girl = 0;
	}

	void CGameStateRun::LoadGameBitmap()//只执行一次
	{
		background.LoadBitmap("RES\\background.bmp");
		////初始化菜单
		//game_menu = make_shared<Menu>();
		//game_menu->LoadItemBitmap();
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

		//if (flag_game_menu!=0)
		//{
		//	game_menu->OnShow(flag_game_menu);
		//}
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
	void CGameStateRun::MovePlatform(shared_ptr<Player> platform, shared_ptr<Player> player1, shared_ptr<Player> player2)
	{

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
				if (player->is_boy)
				{
					CAudio::Instance()->Play(AUDIO_BOYJUMP, true);
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_GIRLJUMP, true);
				}
				player->SetAni(player->GetUp());
				player->y -= player->velocity;
				player->velocity--;
			}
			else
			{
				//上方不可通行，将flag_fan恢复

				//flag_fan = false;
				if (player->is_boy)
				{
					flag_fan_boy = false;
				}
				else
				{
					flag_fan_girl = false;
				}

				if (player->is_boy)
				{
					CAudio::Instance()->Play(AUDIO_BOYJUMP, false);
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_GIRLJUMP, false);
				}
				player->moving_vertical = DIRECTION_DOWN;//当速度<=0时，垂直方向变为下降
				player->velocity = 1;
				player->SetAni(player->GetDown());

				////上方不可通行，将flag_fan恢复
				//flag_fan = false;
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
					player->velocity = 4;//当直接掉下时初速度为 INITIAL_VELOCITY （跳起初始速度） 而不是1（掉落初始速度）
				}
			}
			else
			{
				player->moving_vertical = DIRECTION_NONE;//当下方不可通行时，垂直方向变成静止
				
				//在风扇上
				if (flag_fan_boy&&player->is_boy || flag_fan_girl && !player->is_boy)
				{
					player->velocity = INITIAL_VELOCITY * 3;//在风扇上
				}
				else
				{
					player->velocity = INITIAL_VELOCITY;//加速度变为初始值
				}
				
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
		bool accessible = true;

		//获取玩家坐标
		PlayerCoordinate coordinate = GetPlayerCoordinate(player);
		const int x1 = coordinate.x1;
		const int y1 = coordinate.y1;
		const int x2 = coordinate.x2;
		const int y2 = coordinate.y2;

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
						ItemInteract(item, player, coordinate, DIRECTION_UP);//与item交互
					}
				}
				break;
			case DIRECTION_DOWN:
				if (item->HitRectangle(x1, y1 + player->GetVelocity(), x2, y2 + player->GetVelocity()))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						ItemInteract(item, player, coordinate, DIRECTION_DOWN);//与item交互
					}
				}
				break;
			case DIRECTION_LEFT:
				if (item->HitRectangle(x1 - player->GetStep(), y1, x2 - player->GetStep(), y2))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						ItemInteract(item, player, coordinate, DIRECTION_LEFT);//与item交互
					}
				}
				break;
			case DIRECTION_RIGHT:
				if (item->HitRectangle(x1 + player->GetStep(), y1, x2 + player->GetStep(), y2))
				{
					accessible = item->is_accessible;
					if (item->is_visibale)
					{
						ItemInteract(item, player, coordinate, DIRECTION_RIGHT);//与item交互
					}
				}
				break;
			default:
				break;
			}

			if (flag_change_level)//jump out
			{
				flag_change_level = false;
				accessible = false;
				break;
			}
		}

		return accessible;
	}

	void CGameStateRun::PlayerDie(shared_ptr<Player> player)//玩家死亡
	{
		if (player->is_boy)
		{
			TRACE("boy die\n");
		}
		else
		{
			TRACE("girl die\n");
		}
		CAudio::Instance()->Play(AUDIO_DIE, true);
		player->is_die = true;
		player->is_visible = false;

		//暂停游戏逻辑
		flag_game_loaded = false;
		//分数清零
		score_boy = 0;
		score_girl = 0;
		//游戏结束
		CAudio::Instance()->Play(AUDIO_DIE, false);
		//显示死亡菜单
		flag_game_menu_type = 2;//over menu
		//GotoGameState(GAME_STATE_OVER);
		GotoGameState(GAME_STATE_PAUSE);

		//CAudio::Instance()->Stop(AUDIO_DIE);
		//todo: game over画面显示玩家总分，需要在此处再累加一次
	}

	void CGameStateRun::PlayerReachExit(shared_ptr<Player> player, bool is_arrive)//玩家到达出口
	{
		player->reach_exit = is_arrive;

		if (boy->reach_exit && girl->reach_exit)
		{
			boy->reach_exit = false;
			girl->reach_exit = false;
			//暂停游戏逻辑
			flag_game_loaded = false;
			//准备切换关卡
			flag_change_level = true;
			//玩家分数累加到总分
			score_boy += boy->score;
			score_girl += girl->score;
			//显示暂停菜单
			//切换关卡
			flag_now_level++;
			InitMapLevel(flag_now_level);

			//显示暂停菜单
			flag_game_menu_type = 1;//pause menu
			GotoGameState(GAME_STATE_PAUSE);
		}
	}

	PlayerCoordinate CGameStateRun::GetPlayerCoordinate(shared_ptr<Player> player)//获取玩家座标
	{
		PlayerCoordinate coordinate;

		coordinate.x1 = player->GetX1();
		coordinate.y1 = player->GetY1();
		coordinate.x2 = player->GetX2();
		coordinate.y2 = player->GetY2();

		return coordinate;
	}

	//void CGameStateRun::ShowPauseMenu()
	//{
	//	TRACE("wait for mouse click\n");
	//	//等待鼠标点击
	//	while (true)
	//	{
	//		if (mouse_click == 1)
	//		{
	//			mouse_click = 0;
	//			break;
	//		}
	//	}
	//	TRACE("mouse click\n");
	//}
}
