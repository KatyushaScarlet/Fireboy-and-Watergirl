#pragma once

#include "Menu.h"

#include<memory>

namespace game_framework {
	class CGameStatePause :public CGameState
	{
	public:
		CGameStatePause(CGame* g);
		~CGameStatePause();
		void OnBeginState();							// �O��ÿ�����������׃��
		void OnInit();  								// �[��ĳ�ֵ���D���O��
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // ̎����Ą���
		void OnLButtonUp(UINT nFlags, CPoint point);	// ̎����Ą���
		void OnMouseMove(UINT nFlags, CPoint point);	// ̎����Ą��� 
		void OnRButtonDown(UINT nFlags, CPoint point);  // ̎����Ą���
		void OnRButtonUp(UINT nFlags, CPoint point);	// ̎����Ą���
	protected:
		void OnMove();									// �Ƅ��[��Ԫ��
		void OnShow();

	private:
		shared_ptr<Menu> game_menu;

		int mouse_x;
		int mouse_y;
	};
}