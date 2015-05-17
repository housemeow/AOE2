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
#include "CMouse.h"
#include "CResourceCenter.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CConvert.h"

#include "CFruit.h"
#include "CGold.h"
#include "CWood.h"
#include "CStone.h"

#include "CKnight.h"
#include "CArcher.h"
#include "CSwordMan.h"
#include "CVillager.h"


#include "CTownCenter.h"
#include "CBarrack.h"
#include "CArchery.h"
#include "CStable.h"
#include "CBuildingBuilder.h"
#include "CInitDialog.h"
#include "mygame.h"

namespace game_framework {

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

CMovingBitmap bmp1,bmp2;
void CGameStateInit::OnInit()
{
	CBitmapCollection::GetBitmapCollection();
	/*bmp1.LoadBitmapA("Bitmaps/People",0);
	bmp2.LoadBitmapA("",0);*/
	CAudio::Instance()->Load(AUDIO_START,"sounds\\xopen.mp3");
	CAudio::Instance()->Play(AUDIO_START,true);
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	mouse = CMouse::GetMouse();
	startDialog = CStartDialog::GetStartDialog();
	logo.LoadBitmapA("CON_LOGO.BMP",RGB(255,255,255));
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
	startDialog=CStartDialog::GetStartDialog();
	endDialog=CEndDialog::GetEndDialog();
	helpDialog=CHelpDialog::GetHelpDialog();
	
	cursor.LoadBitmapA("Bitmaps/Cursors/mcursors.shp 0000.bmp",0);
}


void CGameStateInit::OnBeginState()
{
	CAudio::Instance()->Play(AUDIO_START,true);

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	mouse->MouseState().SetLeftDownPoint(point);
	mouse->MouseState().SetLeftIsDown(true);
	if(CStartDialog::GetStartDialog()->PtInRect(point)){
		GotoGameState(GAME_STATE_RUN);
	}else if(CHelpDialog::GetHelpDialog()->PtInRect(point)){
		GotoGameState(GAME_STATE_HELP);
	}else if(CEndDialog::GetEndDialog()->PtInRect(point)){
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);
	}
	//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}
void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point){	// �B�z�ƹ����ʧ@
	CMouse::GetMouse()->MouseState().SetLeftIsDown(false);
}
void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point){  // �B�z�ƹ����ʧ@
	CMouse::GetMouse()->MouseState().SetRightDownPoint(point);
	CMouse::GetMouse()->MouseState().SetRightIsDown(true);
}
void CGameStateInit::OnRButtonUp(UINT nFlags, CPoint point){	// �B�z�ƹ����ʧ@
	CMouse::GetMouse()->MouseState().SetRightIsDown(false);

}
void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point){
	CMouse::GetMouse()->MouseState().SetNowPoint(point);
	CMouse::GetMouse()->Point() = point;
}

void CGameStateInit::OnMove(){
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	
}


void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	startDialog->onShow();
	endDialog->onShow();
	helpDialog->onShow();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	//CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	//CFont f,*fp;
	//f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	//fp=pDC->SelectObject(&f);					// ��� font f
	//pDC->SetBkColor(RGB(0,0,0));
	//pDC->SetTextColor(RGB(255,255,0));
	//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	//if (ENABLE_GAME_PAUSE)
	//	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	//pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	//CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

	mouse =CMouse::GetMouse();
	cursor.SetTopLeft(mouse->Point().x,mouse->Point().y);
	cursor.ShowBitmap();
}								
CGameStateInit::~CGameStateInit()
{
	startDialog->Dispose();
	endDialog->Dispose();
	helpDialog->Dispose();
}





/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���ѻ����O
/////////////////////////////////////////////////////////////////////////////

CGameStateHelp::CGameStateHelp(CGame *g): CGameState(g){}
void CGameStateHelp::OnInit(){  								// �C������Ȥιϧγ]�w
	helpAnimation.AddBitmap("Bitmaps/Help/1.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/2.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/3.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/4.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/5.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/6.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/7.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/8.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/9.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/10.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/11.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/12.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/13.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/14.bmp");
	helpAnimation.AddBitmap("Bitmaps/Help/15.bmp");
	helpAnimation.SetDelayCount(1);
	cursor.LoadBitmapA("Bitmaps/Cursors/mcursors.shp 0000.bmp",0);
}
void CGameStateHelp::OnBeginState(){							// �]�w�C�������һݪ��ܼ�
	helpAnimation.Reset();
}
void CGameStateHelp::OnKeyDown(UINT, UINT, UINT){				// �B�z��LUp���ʧ@
	if(helpAnimation.IsFinalBitmap()){
		this->GotoGameState(GAME_STATE_INIT);
	}else{
		helpAnimation.OnMove();
	}
}
void CGameStateHelp::OnLButtonDown(UINT nFlags, CPoint point){  // �B�z�ƹ����ʧ@
	if(helpAnimation.IsFinalBitmap()){
		this->GotoGameState(GAME_STATE_INIT);
	}else{
		helpAnimation.OnMove();
	}
}
void CGameStateHelp::OnMouseMove(UINT nFlags, CPoint point){
	CMouse::GetMouse()->Point() = point;
}


CGameStateHelp::~CGameStateHelp(){}

void CGameStateHelp::OnShow(){									// ��ܳo�Ӫ��A���C���e��
	helpAnimation.SetTopLeft(0,0);
	helpAnimation.OnShow();
	CBitmapCollection* bitmapCollection = CBitmapCollection::GetBitmapCollection();
	CMouse* mouse = CMouse::GetMouse();

	cursor.SetTopLeft(mouse->Point().x,mouse->Point().y);
	cursor.ShowBitmap();
}

void CGameStateHelp::OnMove(){
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
}


/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{

}

void CGameStateOver::OnMove()
{
	//counter--;
	//if (counter < 0)
	//	GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	//counter = 30 * 5; // 5 seconds
}

bool CGameStateOver::isWin;
bool& CGameStateOver::IsWin(){return isWin;}


void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	win.LoadBitmapA("Bitmaps/UI/YouWin.bmp",0);
	lose.LoadBitmapA("Bitmaps/UI/YouLose.bmp",0);
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point){  // �B�z�ƹ����ʧ@
	GotoGameState(GAME_STATE_INIT);
}
void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	GotoGameState(GAME_STATE_INIT);
}


void CGameStateOver::OnShow()
{
	if(isWin){
		win.SetTopLeft(0,0);
		win.ShowBitmap();
	}else{
		lose.SetTopLeft(0,0);
		lose.ShowBitmap();
	}
	//CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	//CFont f,*fp;
	//f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	//fp=pDC->SelectObject(&f);					// ��� font f
	//pDC->SetBkColor(RGB(0,0,0));
	//pDC->SetTextColor(RGB(255,255,0));
	//char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	//sprintf(str, "Game Over ! (%d)", counter / 30);
	//pDC->TextOut(240,210,str);
	//pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	//CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
	mouse->Dispose();
	panel->Dispose();
	CPlayer::Dispose();
	
	CGameMap::ReleaseMap();
	CMapTile::ReleaseBitmap();
	CScreenDialog::Dispose();
	CBuildingBuilder::ReleaseBuildingBuilder();
	CBitmapCollection::Dispose();
}

void CGameStateRun::OnBeginState()
{
	isRunning = true;
	CAudio::Instance()->Stop(AUDIO_START);
	CUnit* unit;
	CResource* res;
	CBuilding* building;
	CGameMap::InitMap(100);

	srand((int)(time(NULL)));
	CRect gridRect;
	for(int x=0;x<map->GridSizeX();x++){
		for(int y=0;y<3;y++){
			if(rand()%10>2){
				res = new CWood();
				res->SetPlayer(nature);
				res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			}
		}
		for(int y=map->GridSizeY()-3;y<map->GridSizeY();y++){
			if(rand()%10>2){
				res = new CWood();
				res->SetPlayer(nature);
				res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			}
		}
	}
	//wood build
	for(int y=0;y<map->GridSizeY();y++){
		for(int x=0;x<3;x++){
			if(rand()%10>2){
				res = new CWood();
				res->SetPlayer(nature);
				res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			}
		}
		for(int x=map->GridSizeX()-3;x<map->GridSizeX();x++){
			if(rand()%10>2){
				res = new CWood();
				res->SetPlayer(nature);
				res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			}
		}
	}
	//player position build
	int playersPosition[4]={1,2,3,4};//playersPosition[0]=player, playerPositoin[1]=npc
	for(int i=0;i<30;i++){
		int tempIndex1=rand()%4,tempIndex2=rand()%4;
		int temp = playersPosition[tempIndex1];
		playersPosition[tempIndex1] = playersPosition[tempIndex2];
		playersPosition[tempIndex2] = temp;
	}//mapSize = (100,100)

	///�ڤ��l��
	//�}���l��
	player->ResourceTable() = CResourceTable(1200,1200,1200,1200);
	CPoint townCenterGridPoint;
	switch(playersPosition[0]){//player
		case 1://up
			townCenterGridPoint = CPoint(20,20);
			break;
		case 2://down
			townCenterGridPoint = CPoint(82,82);
			break;
		case 3://left
			townCenterGridPoint = CPoint(23,82);
			break;
		case 4://right
			townCenterGridPoint = CPoint(82,23);
			break;
	}
	map->SetScreenPoint(CConvert::GetScreenPointByGridPoint(townCenterGridPoint)-CPoint(SIZE_X/2,SIZE_Y/2));

	building = new CTownCenter();
	building->SetPlayer(player);
	building->SetComplete(true);
	building->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint));
	building->SetVisionCount();

	unit = new CVillager();
	unit->SetPlayer(player);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(3,3)));
	unit->SetVisionCount();
	
	unit = new CVillager();
	unit->SetPlayer(player);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(-3,3)));
	unit->SetVisionCount();
	
	unit = new CVillager();
	unit->SetPlayer(player);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(3,-3)));
	unit->SetVisionCount();
	//�F��귽��l��
	CRect resourceRects[4];//0=stone,1=gold,2,3=food
	int resourcesPosition[4]={1,2,3,4};//0=stone,1=gold,2=food,3=food
	for(int i=0;i<30;i++){
		int tempIndex1=rand()%4,tempIndex2=rand()%4;
		int temp = resourcesPosition[tempIndex1];
		resourcesPosition[tempIndex1] = resourcesPosition[tempIndex2];
		resourcesPosition[tempIndex2] = temp;
	}
	CSize resourceSize = CSize(6,6);
	for(int i=0;i<4;i++){//resourceRect
		switch(resourcesPosition[i]){
			case 1://up
				resourceRects[i] = CRect(townCenterGridPoint + CPoint(-14,-14),resourceSize);
				break;
			case 2://down
				resourceRects[i] = CRect(townCenterGridPoint + CPoint(7,7),resourceSize);
				break;
			case 3://left
				resourceRects[i] = CRect(townCenterGridPoint + CPoint(-14,7),resourceSize);
				break;
			case 4://right
				resourceRects[i] = CRect(townCenterGridPoint + CPoint(7,-14),resourceSize);
				break;
		}
	}
	for(int x=resourceRects[0].left;x<resourceRects[0].right;x++){//stone
		for(int y=resourceRects[0].top;y<resourceRects[0].bottom;y++){
			if(rand()%10>6)continue;
			res = new CStone();
			res->SetPlayer(nature);
			res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
		}
	}
	for(int x=resourceRects[1].left;x<resourceRects[1].right;x++){//gold
		for(int y=resourceRects[1].top;y<resourceRects[1].bottom;y++){
			if(rand()%10>7)continue;
			res = new CGold();
			res->SetPlayer(nature);
			res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
		}
	}
	for(int x=resourceRects[2].left;x<resourceRects[2].right;x++){//food
		for(int y=resourceRects[2].top;y<resourceRects[2].bottom;y++){
			if(rand()%10>8)continue;
			res = new CFruit();
			res->SetPlayer(nature);
			res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
		}
	}
	for(int x=resourceRects[3].left;x<resourceRects[3].right;x++){//food
		for(int y=resourceRects[3].top;y<resourceRects[3].bottom;y++){
			if(rand()%10>8)continue;
			res = new CFruit();
			res->SetPlayer(nature);
			res->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
		}
	}
	




	//�Ĥ��l��
	//�}���l��
	enemyAttackCount = 0;
	switch(playersPosition[1]){//npc
		case 1://up
			townCenterGridPoint = CPoint(25,25);
			break;
		case 2://down
			townCenterGridPoint = CPoint(80,80);
			break;
		case 3://left
			townCenterGridPoint = CPoint(25,80);
			break;
		case 4://right
			townCenterGridPoint = CPoint(80,25);
			break;
	}
	building = new CTownCenter();
	building->SetPlayer(npc);
	building->SetComplete(true);
	building->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint));
	//�x��
	building = new CBarrack();
	building->SetPlayer(npc);
	building->SetComplete(true);
	building->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint+CPoint(-4,6)));
	CRect unitRect;
	CSize unitSize(3,3);
	unitRect = CRect(townCenterGridPoint+CPoint(-3,7),unitSize);
	for(int x=unitRect.left;x<unitRect.right;x++){
		for(int y=unitRect.top;y<unitRect.bottom;y++){
			unit = new CSwordman();
			unit->SetPlayer(npc);
			unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			unit->SetVisionCount();
		}
	}

	//�g�b��
	building = new CArchery();
	building->SetPlayer(npc);
	building->SetComplete(true);
	building->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint+CPoint(6,-4)));
	unitRect = CRect(townCenterGridPoint+CPoint(7,-3),unitSize);
	for(int x=unitRect.left;x<unitRect.right;x++){
		for(int y=unitRect.top;y<unitRect.bottom;y++){
			unit = new CArcher();
			unit->SetPlayer(npc);
			unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			unit->SetVisionCount();
		}
	}


	//���\
	building = new CStable();
	building->SetPlayer(npc);
	building->SetComplete(true);
	building->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint+CPoint(8,8)));
	unitRect = CRect(townCenterGridPoint+CPoint(9,9),unitSize);
	for(int x=unitRect.left;x<unitRect.right;x++){
		for(int y=unitRect.top;y<unitRect.bottom;y++){
			unit = new CKnight();
			unit->SetPlayer(npc);
			unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(CPoint(x,y)));
			unit->SetVisionCount();
		}
	}

	unit = new CVillager();
	unit->SetPlayer(npc);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(-3,1)));
	unit->SetVisionCount();
	
	unit = new CVillager();
	unit->SetPlayer(npc);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(1,1)));
	unit->SetVisionCount();
	
	unit = new CVillager();
	unit->SetPlayer(npc);
	unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(townCenterGridPoint + CPoint(1,-3)));
	unit->SetVisionCount();

}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//

	map->OnMove();
	if(isRunning){
		set<CSprite*>::iterator it;
		enemyAttackCount++;
		if(enemyAttackCount > 30*180){
			for(it=npc->Sprites().begin();it!=npc->Sprites().end();it++){
				(*it)->targetRange = 100;
			}
		}
		for(it=npc->Sprites().begin();it!=npc->Sprites().end();it++){
			(*it)->FindTarget();
		}
		for(it=player->Sprites().begin();it!=player->Sprites().end();it++){
			(*it)->FindTarget();
		}
		for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
			(*it)->OnMove();
			(*it)->OnAction();
		}
		panel->EraseSprites();
		player->EraseSprites();
		npc->EraseSprites();
		nature->EraseSprites();
		for(it = npc->Sprites().begin();it!=npc->Sprites().end();it++){
			(*it)->OnMove();
			(*it)->OnAction();
		}
		panel->EraseSprites();
		player->EraseSprites();
		npc->EraseSprites();
		nature->EraseSprites();
		for(it = nature->Sprites().begin();it!=nature->Sprites().end();it++){
			(*it)->OnMove();
			(*it)->OnAction();
		}
		panel->EraseSprites();
		player->EraseSprites();
		npc->EraseSprites();
		nature->EraseSprites();

		buildingBuilder->OnMove();

		

		if(npc->Sprites().size()==0 || player->Sprites().size()==0){
			if(npc->Sprites().size()==0){
				isWin = true;
				CAudio::Instance()->Play(AUDIO_WIN,true);
			}else{
				isWin = false;
				CAudio::Instance()->Play(AUDIO_LOSE,true);
			}
			isRunning = false;
			for(int y=0;y<map->GridSizeY();y++){
				for(int x=0;x<map->GridSizeX();x++){
					CMapTile* mapTile = map->GetMapTile(CPoint(x,y));
					mapTile->IsExplored() = true;
					mapTile->VisionCount() =+ 1;
				}
			}
		}
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	screen = CScreenDialog::GetScreenDialog();
	mouse = CMouse::GetMouse();
	panel = CSelectionPanel::GetSelectionPanel();
	bitmapCollection= CBitmapCollection::GetBitmapCollection();
	bitmapCollection->LoadResource();
	buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
	CMapTile::LoadBitmapA();
	CGameMap::InitMap(100);

	map = CGameMap::GetMap();
	map->SetScreenPoint(CPoint(0,0));
	//map->SetScreenViewPointByGrid(CPoint(map->GridSizeX()/2,map->GridSizeY()/2));
	player = CPlayer::GetPlayer();
	npc = CPlayer::GetNPC();
	nature = CPlayer::GetNature();

	top.LoadBitmapA("Bitmaps/UI/top.bmp");
	bottom.LoadBitmapA("Bitmaps/UI/bottom.bmp");
	cursor.LoadBitmapA("Bitmaps/Cursors/mcursors.shp 0000.bmp",0);
	

	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	CAudio::Instance()->Load(AUDIO_READY, "sounds\\ready.wav");	// ���J�s��3���n��ready.wav
	CAudio::Instance()->Load(AUDIO_TOWN, "sounds\\RTWC.wav");	// ���J�s��4���n��ready.wav
	CAudio::Instance()->Load(AUDIO_BARRACK, "sounds\\BRKS.wav");	// ���J�s��5���n��BRKS.wav
	CAudio::Instance()->Load(AUDIO_STABLE, "sounds\\STBL.wav");	// ���J�s��6���n��STBL.wav
	CAudio::Instance()->Load(AUDIO_ARCHERY, "sounds\\ARRG.wav");	// ���J�s��6���n��STBL.wav
	CAudio::Instance()->Load(AUDIO_DEATH, "sounds\\death1.wav");	// ���J�s��6���n��STBL.wav
	CAudio::Instance()->Load(AUDIO_WIN,  "sounds\\WON1.MP3");
	CAudio::Instance()->Load(AUDIO_LOSE, "sounds\\LOST.MP3");
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
	isRunning = true;
}

////////////////////////////////////////////////////////////
////	Keyboard Handler
////////////////////////////////////////////////////////////

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;	 // esc
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_DELETE= 0x2E; // keyboardDELETE��
	if (!isRunning){
		set<CSprite*>::iterator it;
		CAudio::Instance()->Stop(AUDIO_WIN);
		CAudio::Instance()->Stop(AUDIO_LOSE);
		for(it=player->Sprites().begin();it!=player->Sprites().end();it++){
			delete *it;
		}
		for(it=npc->Sprites().begin();it!=npc->Sprites().end();it++){
			delete *it;
		}
		for(it=nature->Sprites().begin();it!=nature->Sprites().end();it++){
			delete *it;
		}
		npc->Sprites().clear();
		player->Sprites().clear();

		nature->Sprites().clear();
		panel->SelectedSprites().clear();
		
		GotoGameState(GAME_STATE_INIT);
	}

	if (nChar == KEY_LEFT){
		map->SetMovingLeft(true);
		TRACE("KEY_LEFT\n");
		return;
	}
	if (nChar == KEY_RIGHT){
		map->SetMovingRight(true);
		TRACE("KEY_RIGHT\n");
		return;
	}
	if (nChar == KEY_UP){
		map->SetMovingUp(true);
		TRACE("KEY_UP\n");
		return;
	}
	if (nChar == KEY_DOWN){
		map->SetMovingDown(true);
		TRACE("KEY_DOWN\n");
		return;
	}
	if (nChar == KEY_DELETE){
		set<CSprite*>::iterator it;
		for(it=panel->SelectedSprites().begin();it!=panel->SelectedSprites().end();it++){
			if((*it)->Player()==player){
				(*it)->OnDie();
				break;
			}
		}
		TRACE("KEY_DELETE\n");
		return;
	}
	switch(nChar){
		case 'l':
		case 'L'://look
			for(int y=0;y<map->GridSizeY();y++){
				for(int x=0;x<map->GridSizeX();x++){
					CMapTile* mapTile = map->GetMapTile(CPoint(x,y));
					mapTile->IsExplored() = true;
					mapTile->VisionCount()+=1;
				}
			}
			break;
		case 'r'://rock
		case 'R':
			player->ResourceTable() += CResourceTable(0,0,0,1000);
			break;//int wood,int food,int gold,int stone
		case 'w'://wood
		case 'W':
			player->ResourceTable() += CResourceTable(1000,0,0,0);
			break;
		case 'g'://gold;
		case 'G':
			player->ResourceTable() += CResourceTable(0,0,1000,0);
			break;
		case 'f'://food
		case 'F':
			player->ResourceTable() += CResourceTable(0,1000,0,0);
			break;
		case 'd':
		case 'D':
			enemyAttackCount = 30*180;
			break;
	}

	CPoint gridPoint = CConvert::GetGridPointByScreenPoint(mouse->Point());
	CConvert::FitGridPoint(gridPoint);
	CGameMap* map = CGameMap::GetMap();
	CMapTile* mapTile = map->GetMapTile(gridPoint);
	if(mapTile->IsEmpty()){
		CUnit* unit;
		switch(nChar){
			case 'v'://Villager
			case 'V':
				unit = new CVillager();
				unit->SetPlayer(player);
				unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(gridPoint));
				unit->SetVisionCount();
				break;
			case 's'://Swordman
			case 'S':
				unit = new CSwordman();
				unit->SetPlayer(player);
				unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(gridPoint));
				unit->SetVisionCount();
				break;
			case 'a'://Archer
			case 'A':
				unit = new CArcher();
				unit->SetPlayer(player);
				unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(gridPoint));
				unit->SetVisionCount();
				break;
			case 'k'://Knight
			case 'K':
				unit = new CKnight();
				unit->SetPlayer(player);
				unit->SetMapPointAndMapTile(CConvert::GetMapPointByGridPoint(gridPoint));
				unit->SetVisionCount();
				break;
		}
	}

	TRACE("nChar=%d\n",nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
	{
		map->SetMovingLeft(false);
		return;
	}
	if (nChar == KEY_RIGHT){
		map->SetMovingRight(false);
		return;
	}
	if (nChar == KEY_UP){
		map->SetMovingUp(false);
		return;
	}
	if (nChar == KEY_DOWN){
		map->SetMovingDown(false);
		return;
	}
}


//////////////////////////////////////////////////////
////     Mouse Handler
//////////////////////////////////////////////////////
//OK
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	mouse->LeftIsDown()=true;
	mouse->LeftDownPoint()=point;
	mouse->OnLeftDown(point);
}
//OK
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	mouse->LeftIsDown()=false;
	if(!mouse->MoveAfterMouseDown()){
		mouse->OnLeftClick(point);
	}
	mouse->OnLeftUp(point);
	//���k�䳣��}�~�NMoveAfterMouseDown�k�s
	if(!mouse->RightIsDown() && !mouse->LeftIsDown()){
		mouse->MoveAfterMouseDown()=false;
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	if(buildingBuilder->IsBuilding()){
		buildingBuilder->CancelBuilding();
		player->EraseSprites();
	}else{
		mouse->RightIsDown()=true;
		mouse->RightDownPoint()=point;
		mouse->OnRightDown(point);
	}
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	mouse->RightIsDown()=false;
	if(!mouse->MoveAfterMouseDown()){
		mouse->OnRightClick(point);
	}
	mouse->OnRightUp(point);
	//���k�䳣��}�~�NMoveAfterMouseDown�k�s
	if(!mouse->RightIsDown() && !mouse->LeftIsDown()){
		mouse->MoveAfterMouseDown()=false;
	}
}
//OK
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point){
	//�a�ϲ���
	if(!panel->IsSelecting()){
		
		if(point.x<10){
			map->SetMovingLeft(true);
		}else if(point.x>780){
			map->SetMovingRight(true);
		}else{
			map->SetMovingLeft(false);
			map->SetMovingRight(false);
		}
		if(point.y<10){
			map->SetMovingUp(true);
		}else if(point.y>580){
			map->SetMovingDown(true);
		}else{
			map->SetMovingUp(false);
			map->SetMovingDown(false);
		}
	}

	//�p�G������Q���U�S���ʪ��� �h�NMoveAfterMouseDown�]��true
	if(mouse->LeftIsDown() || mouse->RightIsDown()){
		mouse->MoveAfterMouseDown()=true;
	}
	mouse->Point() = point;
	mouse->OnMouseMove(point);
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	map->OnShow();
	
	buildingBuilder->OnShow();

	panel->OnShow();
	panel->OnShowHPLine();

	top.SetTopLeft(0,0);
	top.ShowBitmap();
	screen->PlayerDialog.OnShow();
	screen->SmallMapDialog.ShowSmallMap();
	screen->FunctionDialog()->ShowSubDialog();
	screen->ObjectContainDialog.ShowSubDialog();
	screen->ObjectContainDialog.OnShow();


	CPoint screenPoint;
	char str[80];
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(100,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	set<CSprite*>::iterator it;
	for(it=player->Sprites().begin();it!=player->Sprites().end();it++){
		// ��ܦۤv���s���󥪰�
		screenPoint = CConvert::GetScreenPointByMapPoint((*it)->MapPoint());
		//��ܦۤv��id
		sprintf(str,"ID:%d",(*it)->ID());
		pDC->TextOut(screenPoint.x,screenPoint.y,str);
		//��ܦۤv��w��SpriteID
		if((*it)->Target().IsSprite()){
			sprintf(str,"target:%d",(*it)->Target().Sprite()->ID());
			pDC->TextOut(screenPoint.x+40,screenPoint.y-15,str);
		}
		//�����w�ۤv��SpriteID			
		set<CSprite*>::iterator j;
		int count=0;
		for(j=(*it)->targetedSprites.begin();j!=(*it)->targetedSprites.end();j++){
			sprintf(str,"targetme%d",(*j)->ID());
			pDC->TextOut(screenPoint.x-40,screenPoint.y-(count++)*15,str);
		}
		////��ܸ��|
		count=0;
		//while(!(*it)->Target().Path.empty()){
		//	sprintf(str,"(%d,%d)",(*it)->Target().Path.front().x,(*it)->Target().Path.front().y);
		//	(*it)->Target().Path.pop();
		//	pDC->TextOut(screenPoint.x+60,screenPoint.y-(count++)*15,str);
		//}
		queue<CPoint> tempPath;
		while(!(*it)->Target().Path.empty()){
			tempPath.push((*it)->Target().Path.front());
			(*it)->Target().Path.pop();
			sprintf(str,"(%d,%d)",tempPath.back().x,tempPath.back().y);
			pDC->TextOut(screenPoint.x+80,screenPoint.y-(count++)*15,str);
		}
		while(!tempPath.empty()){
			(*it)->Target().Path.push(tempPath.front());
			tempPath.pop();
		}
	}
	//
	//for(it=npc->Sprites().begin();it!=npc->Sprites().end();it++){
	//	// ��ܦۤv���s���󥪰�
	//	screenPoint = CConvert::GetScreenPointByMapPoint((*it)->MapPoint());
	//	//��ܦۤv��id
	//	sprintf(str,"ID:%d",(*it)->ID());
	//	pDC->TextOut(screenPoint.x,screenPoint.y,str);
	//	//��ܦۤv��w��SpriteID
	//	if((*it)->Target().IsSprite()){
	//		sprintf(str,"target%d",(*it)->Target().Sprite()->ID());
	//		pDC->TextOut(screenPoint.x+40,screenPoint.y-15,str);
	//	}
	//	//�����w�ۤv��SpriteID			
	//	set<CSprite*>::iterator j;
	//	int count=0;
	//	for(j=(*it)->targetedSprites.begin();j!=(*it)->targetedSprites.end();j++){
	//		sprintf(str,"target me%d",(*j)->ID());
	//		pDC->TextOut(screenPoint.x-40,screenPoint.y-(count++)*15,str);
	//	}
	//}
	//for(it=nature->Sprites().begin();it!=nature->Sprites().end();it++){
	//	// ��ܦۤv���s���󥪰�
	//	screenPoint = CConvert::GetScreenPointByMapPoint((*it)->MapPoint());
	//	//��ܦۤv��id
	//	sprintf(str,"%d",(*it)->ID());
	//	pDC->TextOut(screenPoint.x,screenPoint.y,str);
	//	//��ܦۤv��w��SpriteID
	//	if((*it)->Target().IsSprite()){
	//		sprintf(str,"%d",(*it)->Target().Sprite()->ID());
	//		pDC->TextOut(screenPoint.x,screenPoint.y-15,str);
	//	}
	//	//�����w�ۤv��SpriteID			
	//	set<CSprite*>::iterator j;
	//	int count=0;
	//	for(j=(*it)->targetedSprites.begin();j!=(*it)->targetedSprites.end();j++){
	//		sprintf(str,"%d",(*j)->ID());
	//		pDC->TextOut(screenPoint.x+40,screenPoint.y-(count++)*15,str);
	//	}
	//}

	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	if(!isRunning){
		pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f,*fp;
		f.CreatePointFont(300,"Times New Roman");	// ���� font f; 160���16 point���r
		fp=pDC->SelectObject(&f);					// ��� font f
		//pDC->SetBkColor(RGB(0,0,0));
		pDC->SetBkMode(TRANSPARENT);
		if(isWin){
			pDC->SetTextColor(RGB(255,0,0));
			sprintf(str,"�AĹ�F�I �Ы����N��^��D�e��");
		}else{
			pDC->SetTextColor(RGB(255,255,0));
			sprintf(str,"�A��F�I �Ы����N��^��D�e��");
		}
		pDC->TextOutA(120,SIZE_Y/2-30,str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	

	cursor.SetTopLeft(mouse->Point().x,mouse->Point().y);
	cursor.ShowBitmap();
}

}