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
#ifndef GAMELIB_H
#define GAMELIB_H
#include "gamelib.h"
#endif
#include "CConvert.h"
#include "CMapTile.h"
#include "CGameMap.h"
#include <set>
#include "mygame.h"

namespace game_framework {
	////
	////CMapTile
	////
	bool CMapTile::isLoaded = false;
	int const CMapTile::MH = 32;
	int const CMapTile::MW = 64;

	CMovingBitmap* CMapTile::bitmap[];


	CMapTile::CMapTile(){
		LoadBitmap();
		tile = (Tile)0;
		gridPoint = CPoint(0,0);
		isExplored = false;
		visionCount = 0;
	}
	CMapTile::CMapTile(CPoint gridPoint){
		SetPoint(gridPoint);
		isExplored = false;
		visionCount = 0;
	}
	CMapTile::~CMapTile(){}
	void CMapTile::SetPoint(CPoint gridPoint){
		this->gridPoint.x = gridPoint.x;
		this->gridPoint.y = gridPoint.y;
	}

	void CMapTile::SetTile(Tile t){
		tile = t;
	}

	void CMapTile::LoadBitmap(){ 
		if(!isLoaded){
			for(int i=0;i<TILE_COUNT;i++){
				bitmap[i] = new CMovingBitmap();
				char filepath[100];
				sprintf(filepath,"Bitmaps/MapTile/%d.bmp",i);
				bitmap[i]->LoadBitmap(filepath,0);
			}
			isLoaded=true;
		}
	}
	void CMapTile::OnShow(){
		CPoint screenPoint(CConvert::GetScreenPointByGridPoint(this->gridPoint));
		bitmap[tile]->SetTopLeft(screenPoint.x-bitmap[tile]->Width()/2,screenPoint.y);
		bitmap[tile]->ShowBitmap();
		
		//if(((int)sprites.size())>0){
		//	bitmap[RED]->SetTopLeft(screenPoint.x-bitmap[RED]->Width()/2,screenPoint.y);
		//	bitmap[RED]->ShowBitmap();
		//}

		//char str[80];
		//CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		//CFont f,*fp;
		//f.CreatePointFont(120,"Times New Roman");	// 產生 font f; 160表示16 point的字
		//fp=pDC->SelectObject(&f);					// 選用 font f
		//pDC->SetBkColor(RGB(0,0,0));
		//pDC->SetTextColor(RGB(255,255,0));
		//sprintf(str, "%d",this->visionCount);
		//
		//sprintf(str, "(%d,%d)",this->gridPoint.x,this->gridPoint.y);

		//pDC->TextOut(screenPoint.x,screenPoint.y,str);
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void CMapTile::OnShowSprites(){
		set<CSprite*>::iterator it;
		for(it = sprites.begin();it!=sprites.end();it++){
			if((*it)->GridPoint()==this->gridPoint)
				(*it)->OnShow();	
		}
	}

	void CMapTile::ReleaseBitmap(){
		for(int i=0;i<TILE_COUNT;i++){
			delete bitmap[i];
		}
	}

	CMapTile::Tile CMapTile::GetTile(){return tile;}

	bool CMapTile::IsEmpty(){return sprites.empty();}
	set<CSprite*>& CMapTile::Sprites(){return sprites;}
	bool& CMapTile::IsExplored(){return isExplored;}
	int& CMapTile::VisionCount(){return visionCount;}
}