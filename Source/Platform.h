#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Platform : public Item
	{
		//����ƽ̨��ˮƽ��502 platform_horizon������ֱ��503 platform_vertical��
		//��ʼλ�ã�init_x1��init_y1
		//����λ�ã�init_x2��init_y2
	public:
		Platform(int type,int init_x1,int init_y1,int init_x2,int init_y2);
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
		int init_x1;
		int init_y1;
		int init_x2;
		int init_y2;
	};
}