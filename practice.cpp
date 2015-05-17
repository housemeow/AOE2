/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {

/////////////////////////////////////////////////////////////////////////////
// CBall: Ball class
/////////////////////////////////////////////////////////////////////////////

CBall::CBall()
{
	is_alive = true;
	x = y = dx = dy = index = delay_counter = 0;
}

bool CBall::HitEraser(CEraser *eraser)
{
	// �˴����l�Һc�����x�άO�_�I��y
	return HitRectangle(eraser->GetX1(), eraser->GetY1(),
		   eraser->GetX2(), eraser->GetY2());
}

bool CBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	int x1 = x+dx;				// �y�����W��x�y��
	int y1 = y+dy;				// �y�����W��y�y��
	int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
	int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
	//
	// �˴��y���x�λP�ѼƯx�άO�_���涰
	//
	return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
}

bool CBall::IsAlive()
{
	return is_alive;
}

void CBall::LoadBitmap()
{
	bmp.LoadBitmap(IDB_BALL,RGB(0,0,0));			// ���J�y���ϧ�
	bmp_center.LoadBitmap(IDB_CENTER,RGB(0,0,0));	// ���J�y��ߪ��ϧ�
}

void CBall::OnMove()
{
	if (!is_alive)
		return;
	delay_counter--;
	if (delay_counter < 0) {
		delay_counter = delay;
		//
		// �p��y�V����ߪ��첾�qdx, dy
		//
		const int STEPS=18;
		static const int DIFFX[]={35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
		static const int DIFFY[]={0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
		index++;
		if (index >= STEPS)
			index = 0;
		dx = DIFFX[index];
		dy = DIFFY[index];
	}
}

void CBall::SetDelay(int d)
{
	delay = d;
}

void CBall::SetIsAlive(bool alive)
{
	is_alive = alive;
}

void CBall::SetXY(int nx, int ny)
{
	x = nx; y = ny;
}

void CBall::OnShow()
{
	if (is_alive) {
		bmp.SetTopLeft(x+dx,y+dy);
		bmp.ShowBitmap();
		bmp_center.SetTopLeft(x,y);
		bmp_center.ShowBitmap();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBouncingBall: BouncingBall class
/////////////////////////////////////////////////////////////////////////////

CBouncingBall::CBouncingBall()
{
	const int INITIAL_VELOCITY = 20;	// ��l�W�ɳt��
	const int FLOOR = 400;				// �a�O�y��
	floor = FLOOR;
	x = 95; y = FLOOR-1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
	rising = true; 
	initial_velocity = INITIAL_VELOCITY;
	velocity = initial_velocity;
}

void CBouncingBall::LoadBitmap()
{
	char *filename[4]={".\\bitmaps\\ball1.bmp",".\\bitmaps\\ball2.bmp",".\\bitmaps\\ball3.bmp",".\\bitmaps\\ball4.bmp"};
	for (int i = 0; i < 4; i++)	// ���J�ʵe(��4�i�ϧκc��)
		animation.AddBitmap(filename[i], RGB(0,0,0));
}

void CBouncingBall::OnMove()
{
	if (rising) {			// �W�ɪ��A
		if (velocity > 0) {
			y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
			velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
		} else {
			rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
			velocity = 1;	// �U������t(velocity)��1
		}
	} else {				// �U�����A
		if (y < floor-1) {  // ��y�y���٨S�I��a�O
			y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
			velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
		} else {
			y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
			rising = true;	// �����ϼu�A�U���אּ�W��
			velocity = initial_velocity; // ���]�W�ɪ�l�t��
		}
	}
	animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
}

void CBouncingBall::OnShow()
{
	animation.SetTopLeft(x,y);
	animation.OnShow();
}

/////////////////////////////////////////////////////////////////////////////
// CEraser: Eraser class
/////////////////////////////////////////////////////////////////////////////

CEraser::CEraser()
{
	Initialize();
}

int CEraser::GetX1()
{
	return x;
}

int CEraser::GetY1()
{
	return y;
}

int CEraser::GetX2()
{
	return x + animation.Width();
}

int CEraser::GetY2()
{
	return y + animation.Height();
}

void CEraser::Initialize()
{
	const int X_POS = 280;
	const int Y_POS = 400;
	x = X_POS;
	y = Y_POS;
	isMovingLeft = isMovingRight= isMovingUp = isMovingDown = false;
}

void CEraser::LoadBitmap()
{
	animation.AddBitmap(IDB_ERASER1,RGB(255,255,255));
	animation.AddBitmap(IDB_ERASER2,RGB(255,255,255));
	animation.AddBitmap(IDB_ERASER3,RGB(255,255,255));
	animation.AddBitmap(IDB_ERASER2,RGB(255,255,255));
}

void CEraser::OnMove()
{
	const int STEP_SIZE = 2;
	animation.OnMove();
	if (isMovingLeft)
		x -= STEP_SIZE;
	if (isMovingRight)
		x += STEP_SIZE;
	if (isMovingUp)
		y -= STEP_SIZE;
	if (isMovingDown)
		y += STEP_SIZE;
}

void CEraser::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

void CEraser::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}

void CEraser::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}

void CEraser::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}

void CEraser::SetXY(int nx, int ny)
{
	x = nx; y = ny;
}

void CEraser::OnShow()
{
	animation.SetTopLeft(x,y);
	animation.OnShow();
}

}