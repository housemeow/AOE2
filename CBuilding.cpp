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
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
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

	void CBuilding::OnSelected(){			//�n�B�z�A��ܮؤ��u�X�{�@�������p
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		isSelected=true;
		if(panel->SelectedSprites().size()!=1){//�ؿ窱�p�u�����@�Ӹ귽����
			panel->AddSpriteToEraseQueue(this);
			//�H�W��ӳ��|���A�b�ϥ�iterator�M�X���ɭ� �R���L�ᤣ��ϥ�++
			isSelected=false;
			return;
		}
		PlaySelectedSound();
	}

	void CBuilding::OnShowSelectedLine(){
		//�e���
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CPen penBlack;
		CPen penWhite;
		CPen* pOldPen;
		penBlack.CreatePen(PS_SOLID,2,RGB(0,0,0));
		penWhite.CreatePen(PS_SOLID,2,RGB(255,255,255));
		pOldPen = pDC->SelectObject(&penBlack);
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		pDC->MoveTo(screenPoint.x,screenPoint.y);//�e�©��u
		pDC->LineTo(screenPoint.x+gridSize.cx*32,screenPoint.y-gridSize.cy*16);
		pDC->LineTo(screenPoint.x,screenPoint.y-gridSize.cy*32);
		pDC->LineTo(screenPoint.x-gridSize.cx*32,screenPoint.y-gridSize.cy*16);
		pDC->LineTo(screenPoint.x,screenPoint.y);
		pDC->SelectObject(&penWhite);//
		pDC->MoveTo(screenPoint.x,screenPoint.y+1);//�e�թ��u
		pDC->LineTo(screenPoint.x+gridSize.cx*32,screenPoint.y-gridSize.cy*16+1);
		pDC->LineTo(screenPoint.x,screenPoint.y-gridSize.cy*32+1);
		pDC->LineTo(screenPoint.x-gridSize.cx*32,screenPoint.y-gridSize.cy*16+1);
		pDC->LineTo(screenPoint.x,screenPoint.y+1);

		pDC->SelectObject(pOldPen);						//
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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