#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CConvert.h"
#include "CSprite.h"
#include "CResourceTable.h"
#include "CResource.h"
#include "CSelectionPanel.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
/////////////////////////////////////////////////////////////////////////////
	CResource::CResource(){
		isResource = true;
	}

	void CResource::OnSelected(){			//�n�B�z�A��ܮؤ��u�X�{�@�������p
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		isSelected=true;
		if(panel->SelectedSprites().size()!=1){//�ؿ窱�p�u�����@�Ӹ귽����
			panel->AddSpriteToEraseQueue(this);
			//�H�W��ӳ��|���A�b�ϥ�iterator�M�X���ɭ� �R���L�ᤣ��ϥ�++
			isSelected=false;
		}
	}
	void CResource::OnShowSelectedLine(){
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
		pDC->LineTo(screenPoint.x+32,screenPoint.y-16);
		pDC->LineTo(screenPoint.x,screenPoint.y-32);
		pDC->LineTo(screenPoint.x-32,screenPoint.y-16);
		pDC->LineTo(screenPoint.x,screenPoint.y);
		pDC->SelectObject(&penWhite);//
		pDC->MoveTo(screenPoint.x,screenPoint.y+1);//�e�թ��u
		pDC->LineTo(screenPoint.x+32,screenPoint.y-15);
		pDC->LineTo(screenPoint.x,screenPoint.y-31);
		pDC->LineTo(screenPoint.x-32,screenPoint.y-15);
		pDC->LineTo(screenPoint.x,screenPoint.y+1);

		pDC->SelectObject(pOldPen);						//
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
	//void CResource::SetMapPoint(CPoint mapPoint){
	//	CPoint gridPoint(CConvert::GetGridPointByMapPoint(mapPoint));
	//	this->mapPoint = CConvert::GetMapPointByGridPoint(gridPoint)+CPoint(63,63);
	//	CGameMap* map = CGameMap::GetMap();
	//	//mapTile[0][0] = map->GetMapTile(gridPoint);
	//	mapTile = map->GetMapTile(gridPoint);
	//}
	void CResource::FitMapPoint(CPoint mapPoint){
		CPoint gridPoint(CConvert::GetGridPointByMapPoint(mapPoint));
		SetMapPoint(CConvert::GetMapPointByGridPoint(gridPoint)+CPoint(63,63));
	}


}