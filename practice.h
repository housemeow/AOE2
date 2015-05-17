#ifndef PRACTICE_H
#define PRACTICE_H
/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
// �o��class���ѥi�H����L�ηƹ�������l
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class CEraser
{
public:
	CEraser();
	int  GetX1();					// ���l���W�� x �y��
	int  GetY1();					// ���l���W�� y �y��
	int  GetX2();					// ���l�k�U�� x �y��
	int  GetY2();					// ���l�k�U�� y �y��
	void Initialize();				// �]�w���l����l��
	void LoadBitmap();				// ���J�ϧ�
	void OnMove();					// �������l
	void OnShow();					// �N���l�ϧζK��e��
	void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
	void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
	void SetMovingRight(bool flag); // �]�w�O�_���b���k����
	void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
	void SetXY(int nx, int ny);		// �]�w���l���W���y��
protected:
	CAnimation animation;		// ���l���ʵe
	int x, y;					// ���l���W���y��
	bool isMovingDown;			// �O�_���b���U����
	bool isMovingLeft;			// �O�_���b��������
	bool isMovingRight;			// �O�_���b���k����
	bool isMovingUp;			// �O�_���b���W����
};

/////////////////////////////////////////////////////////////////////////////
// �o��class����¶��骺�y
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class CBall
{
public:
	CBall();
	bool HitEraser(CEraser *eraser);						// �O�_�I�����l
	bool IsAlive();											// �O�_����
	void LoadBitmap();										// ���J�ϧ�
	void OnMove();											// ����
	void OnShow();											// �N�ϧζK��e��
	void SetXY(int nx, int ny);								// �]�w��ߪ��y��
	void SetIsAlive(bool alive);							// �]�w�O�_����
	void SetDelay(int d);									// �]�w���઺�t��
protected:
	CMovingBitmap bmp;			// �y����
	CMovingBitmap bmp_center;	// ��ߪ���			
	int x, y;					// ��ߪ��y��
	int dx, dy;					// �y�Z����ߪ��첾�q
	int index;					// �y���u���סv�A0-17���0-360��
	int delay_counter;			// �վ����t�ת��p�ƾ�
	int delay;					// ���઺�t��
	bool is_alive;				// �O�_����
private:
	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���ѷ|�@���u�����y
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class CBouncingBall
{
public:
	CBouncingBall();
	void LoadBitmap();		// ���J�ϧ�
	void OnMove();			// ����
	void OnShow();			// �N�ϧζK��e��
private:
	int x, y;				// �ϧήy��
	int floor;				// �a�O��Y�y��
	bool rising;			// true��W�ɡBfalse��U��
	int initial_velocity;	// ��l�t��
	int velocity;			// �ثe���t��(�I/��)
	CAnimation animation;	// �Q�ΰʵe�@�ϧ�
};

}
#endif