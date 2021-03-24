#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Map.h"


namespace game_framework {
	Map::Map()
	{
		InitMapLevel(0);
	}
	void Map::LoadBitmapMap()//加载图片
	{
		background.LoadBitmap("RES\\background.bmp");
		for each (Item * item in items)
		{
			item->LoadItemBitmap();
		}
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();

	};
	void Map::OnShow()//显示
	{
		//加载背景
		background.SetTopLeft(0, 0);
		background.ShowBitmap();
		//显示物体
		for each (Wall * item in items)
		{
			item->OnShow();
		}
		//加载玩家
		boy->OnShow();
		girl->OnShow();
	};

	void Map::OnMove()//移动
	{
		boy->OnMove(this);
		girl->OnMove(this);
	}

	void Map::KeyDown(int key_value, bool is_boy)//按下方向
	{
		Player* player_ptr;
		if (is_boy)
		{
			player_ptr = boy;
		}
		else
		{
			player_ptr = girl;
		}

		switch (key_value)
		{
		case DIRECTION_UP:
			if (player_ptr->GetVerticalState() == DIRECTION_NONE)
			{
				//TODO: if can move
				player_ptr->SetVerticalState(DIRECTION_UP);
			}
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			if (player_ptr->GetHorizontalState() == DIRECTION_NONE)
			{
				player_ptr->SetHorizontalState(DIRECTION_LEFT);
			}
			break;
		case DIRECTION_RIGHT:
			if (player_ptr->GetHorizontalState() == DIRECTION_NONE)
			{
				player_ptr->SetHorizontalState(DIRECTION_RIGHT);
			}
			break;
		default:
			break;
		}
	}

	void Map::KeyUp(int key_value, bool is_boy)//松开方向
	{
		Player* player_ptr;
		if (is_boy)
		{
			player_ptr = boy;
		}
		else
		{
			player_ptr = girl;
		}

		switch (key_value)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			if (player_ptr->GetHorizontalState() == DIRECTION_LEFT)
			{
				player_ptr->SetHorizontalState(DIRECTION_NONE);
			}
			break;
		case DIRECTION_RIGHT:
			if (player_ptr->GetHorizontalState() == DIRECTION_RIGHT)
			{
				player_ptr->SetHorizontalState(DIRECTION_NONE);
			}
			break;
		default:
			break;
		}
	}
	bool Map::CanMove(Player *player,int direction)//判定是否能移动
	{
		int x1, y1, x2, y2;
		bool accessible = true;
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
					if (item->HitRectangle(x1, y1- player->GetVelocity(), x2, y2- player->GetVelocity()))
					{
						accessible = item->GetAccessible();
						if (accessible == false)
						{
							item->Interact(this);
						}
					}
				break;
			case DIRECTION_DOWN:
					if (item->HitRectangle(x1, y1+ player->GetVelocity(), x2, y2+ player->GetVelocity()))
					{
						accessible = item->GetAccessible();
						if (accessible == false)
						{
							item->Interact(this);
						}
					}
				break;
			case DIRECTION_LEFT:
				
					if (item->HitRectangle(x1- player->GetStep(), y1, x2- player->GetStep(), y2))
					{
						accessible = item->GetAccessible();
						if (accessible == false)
						{
							item->Interact(this);
						}
					}
				break;
			case DIRECTION_RIGHT:
				if (item->HitRectangle(x1+player->GetStep(), y1, x2+ player->GetStep(), y2))
				{
					accessible = item->GetAccessible();
					if (accessible == false)
					{
						item->Interact(this);
					}
				}
				break;
			default:
				break;
			}
		}

		return accessible;
	}

	void Map::AddScore(bool is_boy)//玩家增加分数
	{
		if (is_boy)
		{
			boy->score++;
		}
		else
		{
			girl->score++;
		}
	}

	void Map::PlayerDie(bool is_boy)//玩家死亡
	{
		if (is_boy)
		{
			boy->is_die = true;
		}
		else
		{
			girl->is_die = true;
		}
		//todo 游戏结束
	}

	void Map::PlayerReachExit(bool is_boy)//玩家到达出口
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

	Map::~Map()
	{
		Map::DestroyResources();
	};

	void Map::InitMapLevel(int level)//初始化地图数据 0~9
	{
		now_level = level;
		//DestroyResources();

		int map_level_0[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
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
				default:
					break;
				}
			}
		}
	}
};
