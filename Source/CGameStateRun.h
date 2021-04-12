#pragma once
//#include "Map.h"
#define MAP_SIZE_WIDTH 40
#define MAP_SIZE_HEIGHT 30
#define MAP_GIRD_PIXEL 32

#include "Item.h"
#include "Wall.h"
#include "Diamond.h"
#include "Door.h"
#include "Switch.h"
#include "Platform.h"
#include "Pool.h"
#include "Switch.h"
#include "Player.h"

#include<memory>

namespace game_framework {
	struct PlayerCoordinate
	{
		int x1;
		int y1;
		int x2;
		int y2;
	};
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
		///////////////////////////////////////////////////////////////
		void ResetMap();
		void LoadGameBitmap();
		void LoadItemBitmap();
		void InitMapLevel(int level);//初始化地图数据 0~9
		void MovePlayer(shared_ptr<Player> player);//移动玩家
		bool CanMove(shared_ptr<Player> player, int direction);//判定玩家是否能移动
		void AddScore(bool is_boy);//玩家增加分数
		void PlayerDie(bool is_boy);//玩家死亡
		void PlayerReachExit(bool is_boy,bool value);//玩家到达出口

		PlayerCoordinate GetPlayerCoordinate(bool is_boy);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int now_level;//目前的关卡
		int	map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];//地图数据

		int score_boy = 0;
		int score_girl = 0;

		shared_ptr<Player> boy;
		shared_ptr<Player> girl;

		vector<Item*>		items;//各种物体
		CMovingBitmap	background;//背景

		bool flag_game_loaded = false;
		bool flag_change_level = false;
	};
}