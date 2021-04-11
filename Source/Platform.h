#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Platform : public Item
	{
		//����ƽ̨��ˮƽ��502 platform_horizon������ֱ��503 platform_vertical��
		//��ʼλ�ã�init_1_x��init_1_y
		//����λ�ã�init_2_x��init_2_y
	public:
		Platform(int type,int init_1_x,int init_1_y,int init_2_x,int init_2_y);
		void LoadItemBitmap();
		void OnShow();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
		//ƽ̨�����ش���
		void Trigger(bool is_on);
	protected:
		CMovingBitmap bitmap;
	private:
		//ƽ̨״̬
		int status;			
		//��ʼλ��
		int init_1_x;
		int init_1_y;
		int init_2_x;
		int init_2_y;
	};
}