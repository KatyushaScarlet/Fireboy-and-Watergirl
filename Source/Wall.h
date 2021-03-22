#pragma once


namespace game_framework {

	class Wall
	{
	public:
		Wall()
		{
			width = 1;
			height = 1;
			is_accessible = false;
		}
		virtual void LoadItemBitmap()
		{
			bitmap.LoadBitmapA("RES\\wall.bmp");
		}
		void OnShow()
		{
			bitmap.SetTopLeft(y, x);
			bitmap.ShowBitmap();
		}
		void OnMove();
		void SetTopLeft(int top, int left)// �趨���Ͻ�����
		{
			x = left;
			y = top;
		}
		int  GetX1()			//���Ͻ� x ����
		{
			return x;
		}
		int  GetY1()			//���Ͻ� y ����
		{
			return y;
		}
		int  GetX2()			//���½� x ����
		{
			return x + width;
		}
		int  GetY2()			//���½� y ����
		{
			return y + height;
		}
		bool GetAccessible()//�Ƿ����ͨ��
		{
			return is_accessible;
		}
		bool HitRectangle(int x1, int y1, int x2, int y2)//�Ƿ���ײ
		{
			return (GetX2() >= x1 && x <= x2 && GetY2() >= y1 && y <= y2);
		}
	protected:
		int x, y;//���Ͻ�����
		int width;
		int height;
		bool is_accessible;//�Ƿ��ͨ��
		CMovingBitmap bitmap;
	};
}