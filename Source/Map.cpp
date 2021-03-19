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
		wall.LoadBitmap("RES\\wall.bmp");
		boy->LoadBitmapPlayer();
		girl->LoadBitmapPlayer();

	};
	void Map::OnShow()//��ʾ
	{
		//���ر���
		background.SetTopLeft(0, 0);
		background.ShowBitmap();
		//����ǽ��
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
		//�������
		boy->OnShow();
		girl->OnShow();
		////����������
		//int* top = new int();
		//int* left = new int();
		//Position2ArrayIndex(boy->GetX1(), boy->GetY1(), top, left);
		//TRACE("boy: top=%d,left=%d\n", *top, *left);
		//Position2ArrayIndex(girl->GetX1(), girl->GetY1(), top, left);
		//TRACE("girl: top=%d,left=%d\n", *top, *left);
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

	void Map::Position2ArrayIndex(int x, int y, int* top, int* left)
	{
		*top = (int)y / MAP_GIRD_PIXEL;
		*left = (int)x / MAP_GIRD_PIXEL;
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
		gx = x / MAP_GIRD_PIXEL;
		gy = y / MAP_GIRD_PIXEL;
		switch (direction)
		{
		case DIRECTION_UP:
			return true;
			break;
		case DIRECTION_DOWN:
			return true;
			break;
		case DIRECTION_LEFT:
			return true;
			break;
		case DIRECTION_RIGHT:
			TRACE("gx:%d,gy:%d\n", gx, gy);
			if (map_array[gy][gx] == 0 && x <= 1248 && x >= 0 && y <= 928 && y >= 0) {
				return true;
			}
			else {
				return false;
			}// �]�w1����  
			break;
		
		default:
			
			break;
		}
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
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},
			{1,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
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
