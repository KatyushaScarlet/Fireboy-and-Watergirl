#pragma once
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
#include "Wind.h"
#include "Player.h"
#include "Menu.h"

#include<memory>

namespace game_framework {
	struct PlayerCoordinate
	{
		int x1;
		int y1;
		int x2;
		int y2;
	};

	enum AUDIO_ID {
		AUDIO_DIE,				// 0
		AUDIO_ADV,				// 1
		AUDIO_DIAMOND,				// 2
		AUDIO_GIRLJUMP,				// 2
		AUDIO_BOYJUMP,	// 2
		AUDIO_LAKE,
		AUDIO_DOOR
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
		void MovePlatform(shared_ptr<Player> platform, shared_ptr<Player> player1, shared_ptr<Player> player2);//移动平台
		bool CanMove(shared_ptr<Player> player, int direction);//判定玩家是否能移动
		void PlayerDie(shared_ptr<Player> player);//玩家死亡
		void PlayerReachExit(shared_ptr<Player> player,bool is_arrive);//玩家到达出口

		void ItemInteract(shared_ptr<Item> item, shared_ptr<Player> player, PlayerCoordinate coordinate, int direction);
		//void DeleteItem(shared_ptr<Item> item);//删除元素
		PlayerCoordinate GetPlayerCoordinate(shared_ptr<Player> player);//获取玩家座标

		//void ShowPauseMenu();//显示暂停菜单
		//void ShowOverMenu();//显示结束菜单


	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//int now_level = 0;//目前的关卡
		int	map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];//地图数据
		int show_menu;//是否显示菜单，0：不显示，1：显示过关，2：显示死亡

		//int score_boy = 0;
		//int score_girl = 0;

		shared_ptr<Player> boy;
		shared_ptr<Player> girl;

		//vector<Item*>		items;//各种物体
		vector<shared_ptr<Item>>		item_ptrs;//各种物体
		CMovingBitmap	background;//背景

		bool flag_game_loaded = false;
		bool flag_change_level = false;

		bool flag_fan_boy = false;
		bool flag_fan_girl = false;

		//----------------------------------------------
		//shared_ptr<Menu> game_menu;

		//int flag_game_menu = 0;

		//int mouse_click = 0;
		//int mouse_x = 0;
		//int mouse_y = 0;
		//----------------------------------------------
	};
}