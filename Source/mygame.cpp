/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

#include <windows.h>

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	//ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	background_title.LoadBitmap("RES\\title\\title.bmp");
	background_about.LoadBitmap("RES\\title\\about.bmp");
	//start_text.LoadBitmapA("RES\\STARTTEXT.bmp", RGB(255, 255, 255));
	animation_static_boy.AddBitmap("RES\\player\\title\\boy_static0.bmp", RGB(0, 0, 0));
	animation_static_boy.AddBitmap("RES\\player\\title\\boy_static1.bmp", RGB(0, 0, 0));
	animation_static_boy.AddBitmap("RES\\player\\title\\boy_static2.bmp", RGB(0, 0, 0));
	animation_static_boy.AddBitmap("RES\\player\\title\\boy_static3.bmp", RGB(0, 0, 0));
	animation_static_boy.AddBitmap("RES\\player\\title\\boy_static4.bmp", RGB(0, 0, 0));
	animation_static_girl.AddBitmap("RES\\player\\title\\girl_static0.bmp", RGB(0, 0, 0));
	animation_static_girl.AddBitmap("RES\\player\\title\\girl_static1.bmp", RGB(0, 0, 0));
	animation_static_girl.AddBitmap("RES\\player\\title\\girl_static2.bmp", RGB(0, 0, 0));
	animation_static_girl.AddBitmap("RES\\player\\title\\girl_static3.bmp", RGB(0, 0, 0));
	animation_static_girl.AddBitmap("RES\\player\\title\\girl_static4.bmp", RGB(0, 0, 0));
	animation_static_boy.SetDelayCount(2);
	animation_static_girl.SetDelayCount(2);
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN

	/*
	about: x=530~750, y=830~930
	open origin game: x=350~730, y=490~580
	back to title: x=430~840, y=670~750
	*/
	int x = point.x;
	int y = point.y;
	switch (flag_background_type)
	{
	case 0:
	{
		if (x >= 530 && x <= 750 && y >= 830 && y <= 930)
		{
			//about
			flag_background_type = 1;
		}
		else 
		{
			GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
		}
	}
		break;
	case 1:
	{
		if (x >= 350 && x <= 730 && y >= 490 && y <= 580)
		{
			//open original game
			char* linkChar = "https://html5.gamedistribution.com/a55c9cc9c21e4fc683c8c6857f3d0c75/";
			ShellExecute(NULL, NULL, linkChar, NULL, NULL, SW_SHOWNORMAL);
		}
		else if (x >= 430 && x <= 840 && y >= 670 && y <= 750)
		{
			//back to game title
			flag_background_type = 0;
		}
	}
		break;
	default:
		break;
	}
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
	//TRACE("x=%d,y=%d\n", point.x, point.y);
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	switch (flag_background_type)
	{
	case 0:
		background_title.SetTopLeft(0, 0);
		background_title.ShowBitmap();
		break;
	case 1:
		background_about.SetTopLeft(0, 0);
		background_about.ShowBitmap();
		break;
	default:
		break;
	}

	animation_static_boy.SetTopLeft(400, 740);
	animation_static_boy.OnShow();
	animation_static_boy.OnMove();
	animation_static_girl.SetTopLeft(848, 740);
	animation_static_girl.OnShow();
	animation_static_girl.OnMove();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	//CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	//CFont f, * fp;
	//f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	//fp = pDC->SelectObject(&f);					// 選用 font f
	//pDC->SetBkColor(RGB(0, 0, 0));
	//pDC->SetTextColor(RGB(255, 255, 0));

	//pDC->TextOut(455, 640, "Please click mouse or press SPACE to begin.");
	//pDC->TextOut(5, 810, "Press Ctrl-F to switch in between window mode and full screen mode.");
	//if (ENABLE_GAME_PAUSE)
	//	pDC->TextOut(5, 840, "Press Ctrl-Q to pause the Game.");
	//pDC->TextOut(5, 870, "Press Alt-F4 or ESC to Quit.");
	//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds

	final_score_boy = score_boy;
	filal_score_girl = score_girl;
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	//ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	////
	//// 開始載入資料
	////
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	////
	//// 最終進度為100%
	////
	//ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換

	if (flag_win)
	{
		sprintf(str, "You Win ! (%d)", counter / 30);
	}
	else 
	{
		sprintf(str, "You Lose ! (%d)", counter / 30);
	}
	pDC->TextOut(570, 420, str);

	//todo: fixbug 分数第二次显示被清零
	sprintf(str, "Boy Score: %d", final_score_boy);
	pDC->TextOut(580, 450, str);

	sprintf(str, "Girl Score: %d", filal_score_girl);
	pDC->TextOut(580, 480, str);

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
}