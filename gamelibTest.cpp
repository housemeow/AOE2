/*
 * gamelibTest.cpp: 本檔案儲遊unit test的test cases
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
 *   2005-09-08
 *     Add test cases for CAnimation::Move() and CAnimation::Show().
 *   2006-02-09
 *     Add test cases for CAnimation::testReset() and CAnimation::testIsFinalBitmap().
 *     Fix CAnimation::Move().
 */

#define	 INITGUID
#include "stdafx.h"
#include "game.h"
#include "MainFrm.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "gamelib.h"
#include "mygame.h"

#include <CppUnit/TestCase.h>
#include <CppUnit/TestSuite.h>
#include <CppUnit/TestCaller.h>
#include <CppUnit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

//#pragma warning( disable : 4786 )  // Disable warning messages

using namespace game_framework;

class CMovingBitmapTest : public CppUnit::TestFixture  {
	CPPUNIT_TEST_SUITE( CMovingBitmapTest );
		CPPUNIT_TEST( testLoadBitmap );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()  {
		b = new CMovingBitmap;
	}
	void tearDown() {
		delete b;
	}
	void testLoadBitmap() {
		b->LoadBitmap(IDB_0);
		b->ShowBitmap();
	}
private:
	CMovingBitmap *b;
};

class CAnimationTest : public CppUnit::TestFixture  {
	CPPUNIT_TEST_SUITE( CAnimationTest );
		CPPUNIT_TEST( testShow );
		CPPUNIT_TEST( testMove );
		CPPUNIT_TEST( testReset );
		CPPUNIT_TEST( testIsFinalBitmap );
	CPPUNIT_TEST_SUITE_END();
public:
	void testMove() {
		const int COUNT = 3;
		CAnimation a(COUNT);
		a.AddBitmap(IDB_0);
		a.AddBitmap(IDB_1);
		a.AddBitmap(IDB_2);
		a.AddBitmap(IDB_3);
		//
		// Move() should change current bitmap number (and reset the number if
		//   necessary) whenever delay count is reached.
		//
		for (int k = 0; k < 2; k++) // test for two times (to test reset)
			for (int i=0; i < 4; i++) { // for all 4 bitmaps
				for (int j = 0; j < COUNT-1; j++) { // for delay count
					a.OnMove();
					// count does not change after COUNT-1 moves
					CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == i);
				}
				a.OnMove();
				// count change after COUNT moves
				CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == ((i+1)%4)); // 4 bitmaps
			}
	}
	void testShow() {
		const int COUNT = 3;
		CAnimation a(COUNT);
		a.AddBitmap(IDB_0);
		a.AddBitmap(IDB_1);
		a.AddBitmap(IDB_2);
		//
		// Show() should never change the "current" bitmap so that
		//   onDraw() does not change the appearence of the animation.
		//
		for (int i=0; i < COUNT*3; i++) {
			a.OnShow();
			//TRACE("i=%d CBN=%d\n",i, a.GetCurrentBitmapNumber());
			CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == 0);
		}
	}
	void testReset() {
		const int COUNT = 7;
		CAnimation a(COUNT);
		a.AddBitmap(IDB_0);
		a.AddBitmap(IDB_1);
		int count[]={0, 1, 17, 31, 51};
		for (int i=0; i < sizeof(count)/sizeof(int); i++) {
			int j;
			a.Reset();
			// count is 0 after reset
			CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == 0);
			for (j=0; j < count[i]; j++)
				a.OnMove();
			a.Reset();
			// count is 0 after reset
			CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == 0);
			for (j=0; j < COUNT-1; j++)
				a.OnMove();
			// count is 0 after COUNT-1 moves
			CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == 0);
			a.OnMove();
			// count is 1 after COUNT moves
			CPPUNIT_ASSERT(a.GetCurrentBitmapNumber() == 1);
			// Make sure addbitmap does not alter the beheavior of reset
			a.AddBitmap(IDB_2);
		}
	}
	void testIsFinalBitmap() {
		const int COUNT = 5;
		int i;
		CAnimation a(COUNT);
		a.AddBitmap(IDB_0);
		for (i = 0; i < COUNT+3; i++) {
			// There is only one bitmap, it is always the last bitmap
			CPPUNIT_ASSERT(a.IsFinalBitmap());
			a.OnMove();
		}
		a.AddBitmap(IDB_1);
		a.AddBitmap(IDB_2);
		for (i = 0; i < 2; i++) { // do it twice
			int j;
			for (j=0; j < COUNT*2-1; j++) {
				a.OnMove();
				// There are 3 bitmaps, the first COUNT*2-1 moves does not reach the last bitmap
				CPPUNIT_ASSERT(!a.IsFinalBitmap());
			}
			for (j=0; j < COUNT; j++) {
				a.OnMove();
				// The next COUNT moves stay in the last bitmap
				CPPUNIT_ASSERT(a.IsFinalBitmap());
			}
			a.OnMove();
			// returns to the first bitmap
			CPPUNIT_ASSERT(!a.IsFinalBitmap());
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( CMovingBitmapTest );
CPPUNIT_TEST_SUITE_REGISTRATION( CAnimationTest );