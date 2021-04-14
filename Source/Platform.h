#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Platform : public Item
	{
		//两种平台：水平（502 platform_horizon）、垂直（503 platform_vertical）
		//初始位置：init_1_x、init_1_y
		//激活位置：init_2_x、init_2_y
	public:
		Platform(int type,int init_1_x,int init_1_y,int init_2_x,int init_2_y);
		void LoadItemBitmap();
		void OnShow();
		void OnMove();
		//平台被开关触发
		void Trigger(bool is_on);
	protected:
		CMovingBitmap bitmap;
	private:
		//平台状态
		int status;			
		//初始位置
		int init_1_x;
		int init_1_y;
		int init_2_x;
		int init_2_y;
	};
}