
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>

#include "CGameStateRun.h"

namespace game_framework
{
	void CGameStateRun::InitMapLevel(int level)//��ʼ����ͼ���� 0~9
	{
		//ֹͣ��Ϸ�߼�
		flag_game_loaded = false;
		//��յ�ͼ
		ResetMap();
		//����Ŀǰ�ؿ�
		now_level = level;
		int map_level_0[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,400,0,0,401,0,0,1,0},
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
			{1,0,0,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200,0,0,0,0,0,0,0,201,0,0,0,0,0,1,1,1,1,0},
			{1,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
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

		//��ͼ��ֵ
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

			//��ӻ���

			//platform1
			shared_ptr<Platform> platform1 = make_shared<Platform>(502, 1, 15, 1, 18);
			item_ptrs.push_back(platform1);
			shared_ptr<Switch> platform1_stick = make_shared<Switch>(501, 9, 19);
			platform1_stick->Bind(platform1);//��ƽ̨
			item_ptrs.push_back(platform1_stick);

			//platform2
			shared_ptr<Platform> platform2 = make_shared<Platform>(502, 34, 12, 34, 15);
			item_ptrs.push_back(platform2);
			shared_ptr<Switch> platform2_button1 = make_shared<Switch>(500, 10, 14);
			shared_ptr<Switch> platform2_button2 = make_shared<Switch>(500, 30, 10);
			platform2_button1->Bind(platform2);//��ƽ̨
			platform2_button2->Bind(platform2);//��ƽ̨
			item_ptrs.push_back(platform2_button1);
			item_ptrs.push_back(platform2_button2);

			//platform3
			shared_ptr<Platform> platform3 = make_shared<Platform>(502, 50, 50, 6, 7);
			item_ptrs.push_back(platform3);
			shared_ptr<Switch> platform3_stick = make_shared<Switch>(501, 1, 6);
			platform3_stick->Bind(platform3);//��ƽ̨
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

			//��ӻ���

			//platform1
			shared_ptr<Platform> platform1 = make_shared<Platform>(503, 19, 16, 19, 10);
			item_ptrs.push_back(platform1);
			shared_ptr<Switch> platform1_button1 = make_shared<Switch>(500, 5, 19);
			shared_ptr<Switch> platform1_button2 = make_shared<Switch>(500, 33, 19);
			platform1_button1->Bind(platform1);//��ƽ̨
			platform1_button2->Bind(platform1);//��ƽ̨
			item_ptrs.push_back(platform1_button1);
			item_ptrs.push_back(platform1_button2);

			//platform2
			shared_ptr<Platform> platform2 = make_shared<Platform>(502, 17, 1, 17, 5);
			item_ptrs.push_back(platform2);
			shared_ptr<Switch> platform2_button1 = make_shared<Switch>(500, 12, 4);
			shared_ptr<Switch> platform2_button2 = make_shared<Switch>(500, 26, 4);
			platform2_button1->Bind(platform2);//��ƽ̨
			platform2_button2->Bind(platform2);//��ƽ̨
			item_ptrs.push_back(platform2_button1);
			item_ptrs.push_back(platform2_button2);

			break;
		}
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
					shared_ptr<Item> fire_pool = make_shared<Pool>(300);
					fire_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(fire_pool);
					break;
				}
				case 301:
				{
					shared_ptr<Item> water_pool = make_shared<Pool>(301);
					water_pool->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_pool);
					break;
				}
				case 302:
				{
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
					water_door->SetTopLeft(MAP_GIRD_PIXEL * i, MAP_GIRD_PIXEL * j);
					item_ptrs.push_back(water_door);
					break;
				}
				default:
					break;
				}
			}
		}

		LoadItemBitmap();
		//������Ϸ�߼�
		flag_game_loaded = true;
	}
}