#pragma once

namespace game_framework {
	class Item
	{
	public:
		~Item() {};
		void LoadBitmap();
		void OnShow();//��ʾ
		void OnMove();//�ƶ�
		void Interact();//�������������
		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
	protected:
		int x1, y1, x2, y2;//���Ͻ�����

	};
}