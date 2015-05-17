#ifndef PRACTICE_H
#define PRACTICE_H
/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
*/

/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class提供可以用鍵盤或滑鼠控制的擦子
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class CEraser
{
public:
	CEraser();
	int  GetX1();					// 擦子左上角 x 座標
	int  GetY1();					// 擦子左上角 y 座標
	int  GetX2();					// 擦子右下角 x 座標
	int  GetY2();					// 擦子右下角 y 座標
	void Initialize();				// 設定擦子為初始值
	void LoadBitmap();				// 載入圖形
	void OnMove();					// 移動擦子
	void OnShow();					// 將擦子圖形貼到畫面
	void SetMovingDown(bool flag);	// 設定是否正在往下移動
	void SetMovingLeft(bool flag);	// 設定是否正在往左移動
	void SetMovingRight(bool flag); // 設定是否正在往右移動
	void SetMovingUp(bool flag);	// 設定是否正在往上移動
	void SetXY(int nx, int ny);		// 設定擦子左上角座標
protected:
	CAnimation animation;		// 擦子的動畫
	int x, y;					// 擦子左上角座標
	bool isMovingDown;			// 是否正在往下移動
	bool isMovingLeft;			// 是否正在往左移動
	bool isMovingRight;			// 是否正在往右移動
	bool isMovingUp;			// 是否正在往上移動
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供繞圈圈的球
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class CBall
{
public:
	CBall();
	bool HitEraser(CEraser *eraser);						// 是否碰到擦子
	bool IsAlive();											// 是否活著
	void LoadBitmap();										// 載入圖形
	void OnMove();											// 移動
	void OnShow();											// 將圖形貼到畫面
	void SetXY(int nx, int ny);								// 設定圓心的座標
	void SetIsAlive(bool alive);							// 設定是否活著
	void SetDelay(int d);									// 設定旋轉的速度
protected:
	CMovingBitmap bmp;			// 球的圖
	CMovingBitmap bmp_center;	// 圓心的圖			
	int x, y;					// 圓心的座標
	int dx, dy;					// 球距離圓心的位移量
	int index;					// 球的「角度」，0-17表示0-360度
	int delay_counter;			// 調整旋轉速度的計數器
	int delay;					// 旋轉的速度
	bool is_alive;				// 是否活著
private:
	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供會一直彈跳的球
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class CBouncingBall
{
public:
	CBouncingBall();
	void LoadBitmap();		// 載入圖形
	void OnMove();			// 移動
	void OnShow();			// 將圖形貼到畫面
private:
	int x, y;				// 圖形座標
	int floor;				// 地板的Y座標
	bool rising;			// true表上升、false表下降
	int initial_velocity;	// 初始速度
	int velocity;			// 目前的速度(點/次)
	CAnimation animation;	// 利用動畫作圖形
};

}
#endif