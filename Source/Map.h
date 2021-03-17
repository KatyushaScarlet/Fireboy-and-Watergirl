#pragma once

#define MAP_SIZE_WIDTH 40
#define MAP_SIZE_HEIGHT 30
#define MAP_GIRD_PIXEL 32

#include "gamelib.h"
#include "Item.h"
#include "Diamond.h"
#include "Door.h"
#include "MovingBox.h"
#include "MovingWall.h"
#include "Pool.h"
#include "Switch.h"

namespace game_framework {
	class Map
	{
	public:
		virtual ~Map() 
		{
			for each (Diamond * item in diamonds)
			{
				delete item;
			}
			for each (Door * item in doors)
			{
				delete item;
			}
			for each (MovingBox * item in moving_boxs)
			{
				delete item;
			}
			for each (MovingWall * item in moving_walls)
			{
				delete item;
			}
			for each (Pool * item in pools)
			{
				delete item;
			}
			for each (Switch * item in switchs)
			{
				delete item;
			}
		};
		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;//显示
		virtual void OnMove() = 0;//移动
		virtual void Interact() = 0;//与各种物件交互

	protected:
		int	map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];//地图数据
		CMovingBitmap	background;//背景
		CMovingBitmap	wall;//墙面

		vector<Diamond*>	diamonds;//钻石
		vector<Door*>	doors;//门
		vector<MovingBox*>	moving_boxs;//可活动箱子
		vector<MovingWall*>	moving_walls;//可活动箱子
		vector<Pool*>		pools;//水池
		vector<Switch*>		switchs;//开关
	};
}