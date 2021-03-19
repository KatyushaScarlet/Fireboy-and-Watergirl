#pragma once


namespace game_framework {
	class Map;
	class Player
	{
	public:
		Player(bool boy);
		~Player();
		void LoadBitmapPlayer();//����ͼ��
		void OnMove(Map* m);//�ƶ�
		void OnShow();//��ʾ
		int  GetX();//��ȡ���ĵ�x
		int  GetY();//��ȡ���ĵ�y
		int  GetX1();//��ȡ���Ͻ�x
		int  GetY1();//��ȡ���Ͻ�y
		int  GetX2();//��ȡ���½�x
		int  GetY2();//��ȡ���½�y
		void SetTopLeft(int top, int left);// �趨���Ͻ�����
		void SetVerticalState(int state);//�趨��ֱ״̬
		void SetHorizontalState(int state);//�趨ˮƽ״̬
		int GetVerticalState();//��ȡ��ֱ״̬
		int GetHorizontalState();//��ȡˮƽ״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x, y;//���ĵ�����
		int moving_vertical, moving_horizontal;//�ƶ���״̬
		int  initial_velocity;// ��ʼ�ٶ�
		int  velocity;// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;// �Ƿ����к�����
		bool is_visible;// �Ƿ�ɼ�
		CMovingBitmap bitmap;// ��ֹͼ��
	};
}