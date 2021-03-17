#pragma once

namespace game_framework {
	class Item
	{
	public:
		virtual ~Item() {};
		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;//��ʾ
		virtual void OnMove() = 0;//�ƶ�
		virtual void Interact() = 0;//�������������
	};
}