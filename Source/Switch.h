#pragma once

#include"Item.h"

namespace game_framework {
	enum SWITCH_STATUS
	{
		SWITCH_RELEASE,
		SWITCH_PRESS
	};
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
		CMovingBitmap bitmap_switch_on;
		CMovingBitmap bitmap_switch_off;
	private:
		//����״̬
		int status = 0;
		bool is_on = false;
		//���ذ󶨵�ƽ̨
		Platform* bind_platform;
	};
}