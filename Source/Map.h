#pragma once
#define MAP_SIZE_WIDTH 40
#define MAP_SIZE_HEIGHT 30
#define MAP_GIRD_PIXEL 32

#include "Item.h"
#include "Wall.h"
#include "Diamond.h"
#include "Door.h"
#include "MovingBox.h"
#include "MovingWall.h"
#include "Pool.h"
#include "Switch.h"
#include "Player.h"

namespace game_framework {

	class Map
	{
	public:
		Map();
		~Map();
		void LoadBitmapMap();//加载图片
		void OnShow();//显示
		void OnMove();//移动
		void KeyDown(int key_value, bool is_boy);//按下方向
		void KeyUp(int key_value, bool is_boy);//松开方向
		void InitMapLevel(int level);//初始化地图数据 0~9
		//////////////////////////////////////////////////////////
		bool CanMove(Player* player, int direction);//判定玩家是否能移动
		void AddScore(bool is_boy);//玩家增加分数
		void PlayerDie(bool is_boy);//玩家死亡
		void PlayerReachExit(bool is_boy);//玩家到达出口
	private:
		int now_level;//目前的关卡
		int	map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];//地图数据

		int score_boy = 0;
		int score_girl = 0;

		CMovingBitmap	background;//背景
		Player* boy;
		Player* girl;
		vector<Item*>		items;//各种物体
	};
}