#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CConvert.h"
#include "CBuilding.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為所有地圖中單位與建築物的基底類別
/////////////////////////////////////////////////////////////////////////////

	CBuilding::CBuilding(){
		isAttackable=true;
		isCollectable=false;
		isRepairable=true;
		isComplete=false;
		isBuilding = true;
		viewDistance = 10;
	}
	CBuilding::~CBuilding(){}

	void CBuilding::OnSelected(){			//要處理再選擇框內只出現一次的狀況
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		isSelected=true;
		if(panel->SelectedSprites().size()!=1){//框選狀況只能選取一個資源物件
			panel->AddSpriteToEraseQueue(this);
			//以上兩個都會錯，在使用iterator尋訪的時候 刪除過後不能使用++
			isSelected=false;
			return;
		}
		PlaySelectedSound();
	}

	void CBuilding::OnShowSelectedLine(){
		//畫圓圈
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CPen penBlack;
		CPen penWhite;
		CPen* pOldPen;
		penBlack.CreatePen(PS_SOLID,2,RGB(0,0,0));
		penWhite.CreatePen(PS_SOLID,2,RGB(255,255,255));
		pOldPen = pDC->SelectObject(&penBlack);
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		pDC->MoveTo(screenPoint.x,screenPoint.y);//畫黑底線
		pDC->LineTo(screenPoint.x+gridSize.cx*32,screenPoint.y-gridSize.cy*16);
		pDC->LineTo(screenPoint.x,screenPoint.y-gridSize.cy*32);
		pDC->LineTo(screenPoint.x-gridSize.cx*32,screenPoint.y-gridSize.cy*16);
		pDC->LineTo(screenPoint.x,screenPoint.y);
		pDC->SelectObject(&penWhite);//
		pDC->MoveTo(screenPoint.x,screenPoint.y+1);//畫白底線
		pDC->LineTo(screenPoint.x+gridSize.cx*32,screenPoint.y-gridSize.cy*16+1);
		pDC->LineTo(screenPoint.x,screenPoint.y-gridSize.cy*32+1);
		pDC->LineTo(screenPoint.x-gridSize.cx*32,screenPoint.y-gridSize.cy*16+1);
		pDC->LineTo(screenPoint.x,screenPoint.y+1);

		pDC->SelectObject(pOldPen);						//
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void CBuilding::FitMapPoint(CPoint mapPoint){
		CPoint gridPoint(CConvert::GetGridPointByMapPoint(mapPoint));
		SetMapPoint(CConvert::GetMapPointByGridPoint(gridPoint)+CPoint(63,63));
	}
	void CBuilding::OnRepaired(CSprite* sprite){
		hp+=3;
		if(hp>=maxHp){
			hp=maxHp;
			isComplete=true;
			set<CSprite*>::iterator it;
			for(it=targetedSprites.begin();it!=targetedSprites.end();it++){
				(*it)->SetTarget(CTarget::Null());
			}
			targetedSprites.clear();
		}
	}
	
	void CBuilding::SetHP(int hp){
		this->hp = hp;
		if(hp==maxHp){
			isComplete=true;
		}
	}
	void CBuilding::SetComplete(bool complete){isComplete = complete;}
}