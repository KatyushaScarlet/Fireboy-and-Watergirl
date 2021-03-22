#pragma once

namespace game_framework {
	class Item
	{
	public:
		virtual void LoadItemBitmap() = 0;	//����λͼ
		virtual void OnShow() = 0;			//��ʾ
		void OnMove();			//�ƶ�
		void Interact();			//�������������
		void SetTopLeft(int top, int left);// �趨���Ͻ�����
		int  GetX1();			//���Ͻ� x ����
		int  GetY1();			//���Ͻ� y ����
		int  GetX2();			//���½� x ����
		int  GetY2();			//���½� y ����
		bool GetAccessible();	//�Ƿ��ͨ��
		bool GetVisibale();		//�Ƿ�ɼ�
		bool HitRectangle(int x1, int y1, int x2, int y2);//�Ƿ���ײ
	protected:
		int x, y;				//���Ͻ�����
		int width;				//��
		int height;				//��
		bool is_accessible;		//�Ƿ��ͨ��
		bool is_visibale;		//�Ƿ�ɼ�
	};
}