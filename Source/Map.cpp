#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework 
{
	Map::Map()
	{

	}
	void Map::LoadMapArray(int map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH])
	{
		for (size_t i = 0; i <   MAP_SIZE_HEIGHT; i++)
		{
			for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
			{
				map[i][j] = map_array[i][j];
			}
		}
	}

	void Map::LoadBitmap()
	{
		background_ingame.LoadBitmapA(IDB_BACKGROUND_INGAME);
		wall.LoadBitmapA(IDB_WALL);
	}

	void Map::OnShow()
	{
		//渲染背景图
		background_ingame.SetTopLeft(0, 0);
		background_ingame.ShowBitmap();
		//渲染墙壁
		for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
		{
			for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
			{
				switch (map[i][j])
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
	}

	Map::~Map()
	{
		
	}
}
