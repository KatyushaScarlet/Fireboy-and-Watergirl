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
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void SetTopLeft(int top, int left);// �趨���Ͻ�����
		void SetVerticalState(int state);//�趨��ֱ״̬
		void SetHorizontalState(int state);//�趨ˮƽ״̬
		int GetVerticalState();//��ȡ��ֱ״̬
		int GetHorizontalState();//��ȡˮƽ״̬
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);//��ײ���

	private:
		int x, y;//����
		int moving_vertical, moving_horizontal;//�ƶ���״̬
		int  initial_velocity;// ��ʼ�ٶ�
		int  velocity;// Ŀǰ���ٶ�(pixel/frame)
		bool is_boy;// �Ƿ����к�����
		bool is_visible;// �Ƿ�ɼ�
		CMovingBitmap bitmap;// ��ֹͼ��
	};
}