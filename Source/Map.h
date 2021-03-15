#pragma once

#define MAP_SIZE_WIDTH 40
#define MAP_SIZE_HEIGHT 30
#define MAP_GIRD_PIXEL 32

#include "gamelib.h"
#include "Diamond.h"
#include "Door.h"
#include "MovingBox.h"
#include "MovingWall.h"
#include "Player.h"
#include "Pool.h"
#include "Switch.h"

namespace game_framework {
	class Map
	{
	public:
		virtual ~Map() {};
		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;//��ʾ
		virtual void OnMove() = 0;//�ƶ�
		virtual void Interact() = 0;//������������
	private:
		int	map[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];//��ͼ����
		CMovingBitmap	background;//����
		CMovingBitmap	wall;//ǽ��

		vector<Diamond*>	diamonds;//��ʯ
		vector<Door*>	doors;//��
		vector<MovingBox*>	moving_boxs;//�ɻ����
		vector<MovingWall*>	moving_walls;//�ɻ����
		vector<Player*>		players;//���
		vector<Pool*>		pools;//ˮ��
		vector<Switch*>		switchs;//����
	};
}