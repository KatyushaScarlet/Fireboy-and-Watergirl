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
	void Map::LoadBitmapMap()//����ͼƬ
	{
		background.LoadBitmap("RES\\background.bmp");
		for each (Item * item in items)
		{
			item->LoadItemBitmap();
		}
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();

	};
	void Map::OnShow()//��ʾ
	{
		//���ر���
		background.SetTopLeft(0, 0);
		background.ShowBitmap();
		//��ʾ����
		for each (Wall * item in items)
		{
			item->OnShow();
		}
		//�������
		boy->OnShow();
		girl->OnShow();
	};

	void Map::OnMove()//�ƶ�
	{
		boy->OnMove(this);
		girl->OnMove(this);
	}

	void Map::KeyDown(int key_value, bool is_boy)//���·���
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

	void Map::KeyUp(int key_value, bool is_boy)//�ɿ�����
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

	bool  Map::PlayerCanMove(int x, int y, int direction)//�ж��Ƿ����ƶ�
	{
		//Position2ArrayIndex(x, y, top, left);

		int top = y / MAP_GIRD_PIXEL;
		int left = x / MAP_GIRD_PIXEL;

		//TRACE("top=%d,left=%d\n", top, left);
		if (map_array[top][left] != 1)
		{
			return true;
		}
		else
		{
			return false;
		}
		//switch (direction)
		//{
		//case DIRECTION_UP:
		//	return true;
		//	break;
		//case DIRECTION_DOWN:
		//	return true;
		//	break;
		//case DIRECTION_LEFT:
		//	TRACE("top=%d,left=%d\n", top, left);
		//	if (map_array[top][left] != 1)
		//	{
		//		return true;
		//	}
		//	else
		//	{
		//		return false;
		//	}
		//	break;
		//case DIRECTION_RIGHT:
		//	TRACE("top=%d,left=%d\n", top, left);
		//	if (map_array[top][left] != 1)
		//	{
		//		return true;
		//	}
		//	else 
		//	{
		//		return false;
		//	}
		//default:
		//	
		//	break;
		//}
	}

	Map::~Map()
	{
		Map::DestroyResources();
	};

	void Map::InitMapLevel(int level)//��ʼ����ͼ���� 0~9
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
		//��ͼ��ֵ
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

		//�������
		for (size_t i = 0; i < MAP_SIZE_HEIGHT; i++)
		{
			for (size_t j = 0; j < MAP_SIZE_WIDTH; j++)
			{
				switch (map_array[i][j])
				{
				case 1:
				{
					Wall* wall = new Wall();
					wall->SetTopLeft(MAP_GIRD_PIXEL * j, MAP_GIRD_PIXEL * i);
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
