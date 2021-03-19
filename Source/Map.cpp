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
		wall.LoadBitmap("RES\\wall.bmp");
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();

	};
	void Map::OnShow()//显示
	{
		//加载背景
		background.SetTopLeft(0, 0);
		background.ShowBitmap();
		//加载墙壁
		for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
		{
			for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
			{
				switch (map_array[i][j])
				{
				case 0:
					break;
				case 1:
					wall.SetTopLeft(MAP_GIRD_PIXEL * j, MAP_GIRD_PIXEL * i);
					wall.ShowBitmap();
				default:
					break;
				}
			}
		}
		//加载玩家
		boy->OnShow();
		girl->OnShow();
		////输出玩家坐标
		//int* top = new int();
		//int* left = new int();
		//Position2ArrayIndex(boy->GetX1(), boy->GetY1(), top, left);
		//TRACE("boy: top=%d,left=%d\n", *top, *left);
		//Position2ArrayIndex(girl->GetX1(), girl->GetY1(), top, left);
		//TRACE("girl: top=%d,left=%d\n", *top, *left);
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
				player_ptr->SetHorizontalState(DIRECTION_UP);
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

	//void Map::Position2ArrayIndex(int x, int y, int* top, int* left)
	//{
	//	*top = (int)y / MAP_GIRD_PIXEL;
	//	*left = (int)x / MAP_GIRD_PIXEL;
	//}

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

	bool  Map::PlayerCanMove(int x, int y, int direction)//判定是否能移动
	{
		//Position2ArrayIndex(x, y, top, left);

		int top = y / MAP_GIRD_PIXEL;
		int left = x / MAP_GIRD_PIXEL;

		switch (direction)
		{
		case DIRECTION_UP:
			return true;
			break;
		case DIRECTION_DOWN:
			return true;
			break;
		case DIRECTION_LEFT:
			TRACE("top=%d,left=%d\n", top, left);
			if (map_array[top][left] != 1)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		case DIRECTION_RIGHT:
			TRACE("top=%d,left=%d\n", top, left);
			if (map_array[top][left] != 1)
			{
				return true;
			}
			else 
			{
				return false;
			}
		default:
			
			break;
		}
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
			{1,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
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
				case 100:
					boy = new Player(true);
					boy->SetTopLeft(i * MAP_GIRD_PIXEL, j * MAP_GIRD_PIXEL);
					break;
				case 101:
					girl = new Player(false);
					girl->SetTopLeft(i * MAP_GIRD_PIXEL, j * MAP_GIRD_PIXEL);
					break;
				default:
					break;
				}
			}
		}
	}
};
