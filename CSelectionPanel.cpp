#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMouse.h"
#include <set>
#include "CSprite.h"
#include "CSelectionPanel.h"
#include "CConvert.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CSelectionPanel: ����Ϊ� class
/////////////////////////////////////////////////////////////////////////////

	CSelectionPanel* CSelectionPanel::panel=NULL;

	CSelectionPanel* CSelectionPanel::GetSelectionPanel(){
		if(panel==NULL){
			panel = new CSelectionPanel();
		}
		return panel;
	}
	void CSelectionPanel::Dispose(){
		delete panel;
		panel=NULL;
	}

	CSelectionPanel::CSelectionPanel(){
		isSelecting=false;
		rect = CRect();
		selectedSprites.clear();
		eraseSprites.clear();
		
	}
	CSelectionPanel::~CSelectionPanel(){}



	void CSelectionPanel::OnClick(const CPoint& point){//�I��
		
		TRACE("CSelection::OnClick\n");
		CPlayer *player,*npc,*nature;
		player = CPlayer::GetPlayer();
		npc = CPlayer::GetNPC();
		nature = CPlayer::GetNature();
		//���M���Ҧ����Sprite
		panel->UnSelected();
		//�Ҧ������a
		set<CSprite*>::iterator it;
		for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
			if((*it)->ScreenRect().PtInRect(point)){
				//�o�ӪF�誺mapTile�O�H�����ӥB�A������
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
					selectedSprites.insert(*it);
					(*it)->OnSelected();
					return;
				}
			}
		}
		for(it = npc->Sprites().begin();it!=npc->Sprites().end();it++){
			if((*it)->ScreenRect().PtInRect(point)){
				//�o�ӪF�誺mapTile�O�H�����ӥB�A������
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
					selectedSprites.insert(*it);
					(*it)->OnSelected();
					return;
				}
			}
		}
		for(it = nature->Sprites().begin();it!=nature->Sprites().end();it++){
			if((*it)->ScreenRect().PtInRect(point)){
				//�o�ӪF�誺mapTile�O�H�����ӥB�A������
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
					selectedSprites.insert(*it);
					(*it)->OnSelected();
					return;
				}
			}
		}
	}

	void CSelectionPanel::OnSelecting(const CRect& rect){//
		
	}

	void CSelectionPanel::OnSelected(const CRect&rect){//�ؿ�
		
		TRACE("CSelection::OnSelected\n");
		CPlayer* player = CPlayer::GetPlayer();
		set<CSprite*>::iterator it;
		//���M���e�������F��
		panel->UnSelected();
		//�Ҧ������a
		int count=0;

		//�p�G��������ئ��涰�A�N����
		for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
			CRect ans;
			if(ans.IntersectRect(rect,(*it)->ScreenRect())){
				selectedSprites.insert(*it);
				count++;
				if(count>=30){
					break;
				}
			}
		}
		for(it=selectedSprites.begin();it!=selectedSprites.end();it++){
			(*it)->OnSelected();
		}
		EraseSprites();
		if(selectedSprites.size()==0){
			CPlayer* npc = CPlayer::GetNPC();
			for(it = npc->Sprites().begin();it!=npc->Sprites().end();it++){
				CRect ans;
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(ans.IntersectRect(rect,(*it)->ScreenRect())){
					if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
						selectedSprites.insert(*it);
						(*it)->OnSelected();
						break;
					}
				}
			}
			EraseSprites();
		}
		if(selectedSprites.size()==0){
			CPlayer* nature = CPlayer::GetNPC();
			for(it = nature->Sprites().begin();it!=nature->Sprites().end();it++){
				CRect ans;
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(ans.IntersectRect(rect,(*it)->ScreenRect())){
					if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
						selectedSprites.insert(*it);
						(*it)->OnSelected();
						break;
					}
				}
			}
			EraseSprites();
		}
		//�̫�
	}

	void CSelectionPanel::UnSelected(){//���U�k���esc�������
		
		isSelecting=false;
		//�M���Ҧ�SelectionPanel������
		set<CSprite*>::iterator it;
		for(it = selectedSprites.begin();it!=selectedSprites.end();it++){
			(*it)->OnUnselected();
		}
		selectedSprites.clear();
	}


	void CSelectionPanel::OnShow(){
		if(isSelecting){
			CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
			CPen p,*pp;									// ø�ϥΪ�������
			p.CreatePen(PS_SOLID,1,RGB(255,0,0));	// �]�w�������
			pp = pDC->SelectObject(&p);					// �N����T�a�JDC
			//pDC->SetDCPenColor(RGB(255,0,0));			// �����D������S��k���C��
			//p.CreatePen(PS_SOLID,1,RGB(255,255,255));
			pDC->MoveTo(rect.TopLeft());				// 
			pDC->LineTo(rect.right,rect.top);			//
			pDC->LineTo(rect.right,rect.bottom);
			pDC->LineTo(rect.left,rect.bottom);
			pDC->LineTo(rect.TopLeft());
			pDC->SelectObject(pp);						//
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}
	}
	
	void CSelectionPanel::AddSpriteToEraseQueue(CSprite* sprite){

		eraseSprites.insert(sprite);
	}
	void CSelectionPanel::EraseSprites(){
		set<CSprite*>::iterator it;
		bool IsEarse;
		if(eraseSprites.size()!=0){
			IsEarse=true;
		}
		else{
			IsEarse=false;
		}
		for(it = eraseSprites.begin();it!=eraseSprites.end();it++){
			selectedSprites.erase(*it);
		}
		eraseSprites.clear();
		if(IsEarse)
		{
				CScreenDialog* sd = CScreenDialog::GetScreenDialog();
				sd->ObjectContainDialog.SelectedObjects();//��sObjectContainDialog
				sd->FunctionDialog()->SetSubDialog();//��sFunctionDialog
		}
	}

	bool& CSelectionPanel::IsSelecting(){
		return isSelecting;
	}
	
	CRect& CSelectionPanel::Rect(){
		return rect;
	}
	
	void CSelectionPanel::SelectSprite(CSprite* sprite){
		set<CSprite*>::iterator it;
		//���M���e�������F��
		isSelecting=false;
		this->UnSelected();
		this->selectedSprites.insert(sprite);
		sprite->OnSelected();
		EraseSprites();
		//�̫�
	}

	set<CSprite*>& CSelectionPanel::SelectedSprites(){
		return selectedSprites;
	}


	void OnShowSelectedLine(){
		
	}

	void CSelectionPanel::OnShowHPLine(){
		set<CSprite*>::iterator it;
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CBrush *pb,redBrush(RGB(255,0,0)),greenBrush(RGB(0,255,0));
		CPen *pp,blackPen(PS_SOLID,1,RGB(0,0,0));
		pp = pDC->SelectObject(&blackPen);

		pb = pDC->SelectObject(&redBrush);
		for(it = selectedSprites.begin();it!=selectedSprites.end();it++){
			CPoint screenPoint(CConvert::GetScreenPointByMapPoint((*it)->MapPoint()));
			CRect redRect(CPoint(screenPoint.x-25,screenPoint.y),CSize(50,5));
			pDC->Rectangle(redRect);

			CRect greenRect(CPoint(screenPoint.x-25,screenPoint.y),CSize(50*(*it)->HP()/(*it)->MaxHP(),5));
			pDC->SelectObject(&greenBrush);
			pDC->Rectangle(greenRect);
			pDC->SelectObject(&redBrush);
		}
		pDC->SelectObject(pb);						//
		pDC->SelectObject(pp);
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		//if(isSelected){
		//	//�e���
		//	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		//	CBrush *pb,redBrush(RGB(255,0,0)),greenBrush(RGB(0,255,0));
		//	CPen *pp,nullPen(PS_NULL,0,RGB(0,0,0));

		//	pb = pDC->SelectObject(&redBrush);
		//	pp = pDC->SelectObject(&nullPen);
		//	CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		//	CRect redRect(CPoint(screenPoint.x-25,screenPoint.y),CSize(50,5));
		//	CRect greenRect(CPoint(screenPoint.x-25,screenPoint.y),CSize(50*hp/maxHp,5));
		//	pDC->Rectangle(redRect);
		//	pDC->SelectObject(&greenBrush);
		//	pDC->Rectangle(greenRect);

		//	pDC->SelectObject(pb);						//
		//	pDC->SelectObject(pp);
		//	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		//}
	}
	

}