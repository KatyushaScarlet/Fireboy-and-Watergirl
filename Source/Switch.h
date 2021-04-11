#pragma once

#include"Item.h"

namespace game_framework {
	class CMovingBitmap;
	class Platform;
	class Switch : public Item
	{
		//���ֿ��أ���ť���ǳ������� 500 switch_button�������ˣ��������� 501 switch_stick��//
		//���˵�����Ϊǽ�ڣ��������·�һ��

	public:
		Switch(int type, int x, int y);
		void LoadItemBitmap();
		void OnShow();
		void Interact(CGameStateRun* game, bool is_boy, int direction);
		//���ذ�ƽ̨
		void Bind(Platform* platform);
	protected:
		CMovingBitmap bitmap;
		CMovingBitmap bitmap_wall;
	private:
		//����״̬
		bool is_on;
		//���ذ󶨵�ƽ̨
		Platform* bind_platform;
	};
}