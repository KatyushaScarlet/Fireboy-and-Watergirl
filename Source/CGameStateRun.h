#pragma once
#include "Map.h"

namespace game_framework {
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		//CBall* ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		//CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		//CBouncingBall   bball;		// 反覆彈跳的球
		///////////////////////////////////////////////
		//int				map_now_level;//游戏目前关卡，0~9
		//vector<Map*>	maps;		//游戏地图
		//Player*			player_boy;	//boy
		//Player*			player_girl;//girl
		Map* map;//地图逻辑
	};
}