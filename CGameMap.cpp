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
#ifndef GAMELIB_H
#define GAMELIB_H
#include "gamelib.h"
#endif
#include "CMapTile.h"
#include "CConvert.h"
#include "CGameMap.h"
#include "CSelectionPanel.h"
#include "mygame.h"


namespace game_framework {
	CGameMap* CGameMap::map=NULL;
	////
	////CGameMap
	////
	void CGameMap::InitMap(int side)
	{//��l�Ƥ@�Ӧa��
		side = (side>MAX_SIDE)?MAX_SIDE:side;//����a�Ͻd��
		side = (side<10) ? 10: side;
		map = CGameMap::GetMap();
		map->sx=map->sy=0;//�i�H���w���N�y�СA�p�G�y�ЬO���X�k���N�|�AOnMove���ɭԮշǡC
		map->isMovingDown = map->isMovingLeft = map->isMovingRight = map->isMovingUp=false;
		map->sizeX = side;
		map->sizeY = side;
		srand(0);
		for(int x=0;x<map->sizeX;x++){
			for(int y=0;y<map->sizeY;y++){
				map->mapTile[y][x].SetPoint(CPoint(x,y));
				map->mapTile[y][x].SetTile(CMapTile::BLACK);//�w�]�Ȭ���
				map->mapTile[y][x].SetTile((CMapTile::Tile)(rand()%CMapTile::TILE_COUNT));//�üƲ���
				if(map->mapTile[y][x].GetTile()==CMapTile::RED){
					map->mapTile[y][x].SetTile((CMapTile::BLACK));
					map->mapTile[y][x].SetPoint(CPoint(x,y));
				}
				map->mapTile[y][x].Sprites().clear();
				map->mapTile[y][x].IsExplored()=false;
				map->mapTile[y][x].VisionCount()=0;
			}
		}
	}
	void CGameMap::ReleaseMap(){delete map; map=NULL;};
	
	CGameMap::CGameMap(){
		fog.LoadBitmapA("Bitmaps/MapTile/fog.bmp",RGB(255,255,255));
	}

	void CGameMap::SetMovingLeft(bool flag){
		this->isMovingLeft = flag;
	}
	void CGameMap::SetMovingRight(bool flag){
		this->isMovingRight = flag;
	}
	void CGameMap::SetMovingUp(bool flag){
		this->isMovingUp = flag;
	}
	void CGameMap::SetMovingDown(bool flag){
		this->isMovingDown = flag;
	}
	void CGameMap::SetScreenPoint(CPoint p){
		this->sx=p.x;
		this->sy=p.y;
	}
	CPoint CGameMap::GetScreenPoint(){
		CPoint p(sx,sy);
		return p;
	};
	int CGameMap::GridSizeX(){return this->sizeX;}
	int CGameMap::GridSizeY(){return this->sizeY;}


	void CGameMap::OnMove(){
		//////////�a�ϰʧ@�}�l//////////
		if(this->isMovingLeft){//��������
				this->sx-=16;
		}
		if(this->isMovingRight){//���k���� 
				this->sx+=16;
		}
		if(this->isMovingUp){//���W����
				this->sy-=8;
		}
		if(this->isMovingDown){//���U����
				this->sy+=8;
		}
		//�ץ��ù��y��
		CPoint mapPoint(CConvert::GetMapPointByScreenPoint(CPoint(400,220)));
		mapPoint.x = mapPoint.x<0? 0: mapPoint.x;
		mapPoint.x = mapPoint.x>=sizeX*64? sizeX*64-1:mapPoint.x;
		mapPoint.y = mapPoint.y<0? 0: mapPoint.y;
		mapPoint.y = mapPoint.y>=sizeY*64? sizeY*64-1:mapPoint.y;
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		sx += screenPoint.x-400;
		sy += screenPoint.y-220;
	}

	void CGameMap::ShowMapTile(){
		CPoint gridPoint(CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6)));
		//���o��Ӧa�Ϫ��d��A�Ω�P�_�O�_�A�a�Ϥ�
		CRect mapRect(0,0,sizeX-1,sizeY-1);
		
		for(int y=0;y<SIZE_Y/32+17;y++){//17���̨Τƪ���
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x+=1;
				gridPoint.y-=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint) && this->mapTile[gridPoint.y][gridPoint.x].IsExplored()){
					
					this->mapTile[gridPoint.y][gridPoint.x].OnShow();
				}
			}
			gridPoint.x+=1;
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x-=1;
				gridPoint.y+=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint) && this->mapTile[gridPoint.y][gridPoint.x].IsExplored()){
					this->mapTile[gridPoint.y][gridPoint.x].OnShow();
				}
			}
			gridPoint.y+=1;
		}

		gridPoint = CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6));
		for(int y=0;y<SIZE_Y/32+17;y++){//17���̨Τƪ���
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x+=1;
				gridPoint.y-=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint) && this->mapTile[gridPoint.y][gridPoint.x].IsExplored()){
					
					//this->mapTile[gridPoint.y][gridPoint.x].OnShow();
				}
			}
			gridPoint.x+=1;
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x-=1;
				gridPoint.y+=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint) && this->mapTile[gridPoint.y][gridPoint.x].IsExplored()){
					//this->mapTile[gridPoint.y][gridPoint.x].OnShow();
				}
			}
			gridPoint.y+=1;
		}



	}

	
	void CGameMap::ShowSprites(){
		CRect mapRect(0,0,sizeX-1,sizeY-1);
		CPoint gridPoint(CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6)));
		//gridPoint = CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6));
		for(int y=0;y<SIZE_Y/32+17;y++){//17���̨Τƪ���
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x+=1;
				gridPoint.y-=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint)){
					if(!mapTile[gridPoint.y][gridPoint.x].IsExplored()){
						continue;
					}
					if(mapTile[gridPoint.y][gridPoint.x].VisionCount()==0){//�����~�u��ܩФl
						set<CSprite*>::iterator it;
						for(it = mapTile[gridPoint.y][gridPoint.x].Sprites().begin();it!= mapTile[gridPoint.y][gridPoint.x].Sprites().end();it++){
							if((*it)->IsBuilding() || (*it)->IsResource()){
								(*it)->OnShow();
							}
						}
					}else{//�A������
						this->mapTile[gridPoint.y][gridPoint.x].OnShowSprites();
					}
				}
			}
			gridPoint.x+=1;
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x-=1;
				gridPoint.y+=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint)){
					if(!mapTile[gridPoint.y][gridPoint.x].IsExplored()){
						continue;
					}
					if(mapTile[gridPoint.y][gridPoint.x].VisionCount()==0){//�����~�u��ܩФl
						set<CSprite*>::iterator it;
						for(it = mapTile[gridPoint.y][gridPoint.x].Sprites().begin();it!= mapTile[gridPoint.y][gridPoint.x].Sprites().end();it++){
							if((*it)->IsBuilding()){
								(*it)->OnShow();
							}
						}
					}else{//�A������
						this->mapTile[gridPoint.y][gridPoint.x].OnShowSprites();
					}
				}
			}
			gridPoint.y+=1;
		}
	}
	void CGameMap::ShowFog(){
		CRect mapRect(0,0,sizeX-1,sizeY-1);
		CPoint gridPoint(CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6)));
		//gridPoint = CConvert::GetGridPointByScreenPoint(CPoint(-64*6,-32*6));
		for(int y=0;y<SIZE_Y/32+17;y++){//17���̨Τƪ���
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x+=1;
				gridPoint.y-=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint)){
					if(mapTile[gridPoint.y][gridPoint.x].VisionCount()==0 && mapTile[gridPoint.y][gridPoint.x].IsExplored()){
						fog.SetTopLeft(screenPoint.x-fog.Width()/2,screenPoint.y);
						fog.ShowBitmap();
					}
				}
			}
			gridPoint.x+=1;
			for(int x=0;x<SIZE_X/64+12;x++){
				gridPoint.x-=1;
				gridPoint.y+=1;
				CPoint screenPoint(CConvert::GetScreenPointByGridPoint(gridPoint));
				if(mapRect.PtInRect(gridPoint)){
					if(mapTile[gridPoint.y][gridPoint.x].VisionCount()==0 && mapTile[gridPoint.y][gridPoint.x].IsExplored()){
						fog.SetTopLeft(screenPoint.x-fog.Width()/2,screenPoint.y);
						fog.ShowBitmap();
					}
				}
			}
			gridPoint.y+=1;
		}
	}
	void CGameMap::OnShow(){
		ShowMapTile();
		ShowSprites();
		ShowFog();
		////
		////�����T��
		//////
		//CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		//CFont f,*fp;
		//f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
		//fp=pDC->SelectObject(&f);					// ��� font f
		//pDC->SetBkColor(RGB(0,0,0));
		//pDC->SetTextColor(RGB(255,255,0));
		//char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		//sprintf(str, "map Screen(%d,%d)",sx,sy);//CGameMap::CConvert::GetGridPointByMapPoint(mp).y);
		//pDC->TextOut(20,370,str);

		//sprintf(str, "mid Screen grid(%d,%d)",
		//	CConvert::GetGridPointByScreenPoint(CPoint(400,220)).x,
		//	CConvert::GetGridPointByScreenPoint(CPoint(400,220)).y

		//	);//CGameMap::CConvert::GetGridPointByMapPoint(mp).y);
		//pDC->TextOut(20,390,str);

		//CMouse* mouse = CMouse::GetMouse();
		//sprintf(str,"mouse GridPoint(%d,%d)",
		//	CConvert::GetGridPointByScreenPoint(mouse->Point()).x,
		//	CConvert::GetGridPointByScreenPoint(mouse->Point()).y);
		//pDC->TextOut(20,310,str);

		//pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		//CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
	CMapTile* CGameMap::GetMapTile(CPoint gridPoint){
		gridPoint.x = (gridPoint.x<0) ? 0 : gridPoint.x;//out of range
		gridPoint.x = (gridPoint.x>=GridSizeX()) ? GridSizeX()-1 : gridPoint.x;
		gridPoint.y = (gridPoint.y<0) ? 0 : gridPoint.y;
		gridPoint.y = (gridPoint.y>=GridSizeY()) ? GridSizeY()-1 : gridPoint.y;
		return &mapTile[gridPoint.y][gridPoint.x];
	}

	int CGameMap::MapSizeX(){//���oMapSize(�@��64)
		return GridSizeX()*64-1;
	}
	int CGameMap::MapSizeY(){//���oMapSize(�@��64)
		return GridSizeY()*64-1;
	}
	CRect CGameMap::GridRect(){
		CRect r(0,0,GridSizeX(),GridSizeY());
		return r;
	}
	CRect CGameMap::MapRect(){
		CRect r(0,0,MapSizeX(),MapSizeY());
		return r;
	}

	bool CGameMap::CanPutHere(CRect rect){
		CGameMap* map = CGameMap::GetMap();
		if((rect & map->GridRect()) !=rect){
			return false;
		}
		//if(!map->MapRect().PtInRect(rect.TopLeft()) || !map->MapRect().PtInRect(rect.BottomRight()))
		//	return false;
		for(int x=rect.left;x<=rect.right;x++){
			for(int y=rect.top;y<=rect.bottom;y++){
				if(map->GetMapTile(CPoint(x,y))->Sprites().empty()==false){
					return false;
				}
			}
		}
		return true;
		//TODO
		//�g�P�_�@��mapPoint�O�_�i�H��F��
		//�g�P�_�@��gridPoint�O�_�i�H��F��
		//�g�P�_�@��rect�O�_�i�H��F��
		//�g���e�P�_�O�_�A�d�� �_�h�����^��false
	}

	bool CGameMap::CanPutHere(CPoint mapPoint){
		CPoint gridPoint(CConvert::GetGridPointByMapPoint(mapPoint));
		return CGameMap::GetMapTile(gridPoint)->Sprites().empty();
	}

	CGameMap* CGameMap::GetMap()
	{
		if(CGameMap::map==NULL){
			map = new CGameMap();
		}
		return map;
	}
	
	void CGameMap::SetScreenViewPointByGrid(CPoint viewpoint)
	{
		map->SetScreenPoint(CPoint((viewpoint.x-viewpoint.y)*32-400,(viewpoint.x+viewpoint.y)*16-220));
	}
}