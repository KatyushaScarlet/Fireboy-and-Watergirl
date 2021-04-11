#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Platform : public Item
	{
		//两种平台：水平（502 platform_horizon）、垂直（503 platform_vertical）
		//初始位置：init_x1、init_y1
		//激活位置：init_x2、init_y2
	public:
		Platform(int type,int init_x1,int init_y1,int init_x2,int init_y2);
		void LoadItemBitmap();
		void OnShow();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
		//平台被开关触发
		void Trigger(bool is_on);
	protected:
		CMovingBitmap bitmap;
	private:
		//平台状态
		int status;			
		//初始位置
		int init_x1;
		int init_y1;
		int init_x2;
		int init_y2;
	};
}