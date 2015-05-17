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
// CSelectionPanel: 選取用的 class
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



	void CSelectionPanel::OnClick(const CPoint& point){//點選
		
		TRACE("CSelection::OnClick\n");
		CPlayer *player,*npc,*nature;
		player = CPlayer::GetPlayer();
		npc = CPlayer::GetNPC();
		nature = CPlayer::GetNature();
		//先清除所有選擇Sprite
		panel->UnSelected();
		//所有的玩家
		set<CSprite*>::iterator it;
		for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
			if((*it)->ScreenRect().PtInRect(point)){
				//這個東西的mapTile是以探索而且再視野內
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
				//這個東西的mapTile是以探索而且再視野內
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
				//這個東西的mapTile是以探索而且再視野內
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

	void CSelectionPanel::OnSelected(const CRect&rect){//框選
		
		TRACE("CSelection::OnSelected\n");
		CPlayer* player = CPlayer::GetPlayer();
		set<CSprite*>::iterator it;
		//先清除容器內的東西
		panel->UnSelected();
		//所有的玩家
		int count=0;

		//如果物件跟選取框有交集，就算選取
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
		//最後
	}

	void CSelectionPanel::UnSelected(){//按下右鍵或esc取消選取
		
		isSelecting=false;
		//清除所有SelectionPanel的物件
		set<CSprite*>::iterator it;
		for(it = selectedSprites.begin();it!=selectedSprites.end();it++){
			(*it)->OnUnselected();
		}
		selectedSprites.clear();
	}


	void CSelectionPanel::OnShow(){
		if(isSelecting){
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CPen p,*pp;									// 繪圖用的筆物件
			p.CreatePen(PS_SOLID,1,RGB(255,0,0));	// 設定筆的資料
			pp = pDC->SelectObject(&p);					// 將筆資訊帶入DC
			//pDC->SetDCPenColor(RGB(255,0,0));			// 不知道為什麼沒辦法改顏色
			//p.CreatePen(PS_SOLID,1,RGB(255,255,255));
			pDC->MoveTo(rect.TopLeft());				// 
			pDC->LineTo(rect.right,rect.top);			//
			pDC->LineTo(rect.right,rect.bottom);
			pDC->LineTo(rect.left,rect.bottom);
			pDC->LineTo(rect.TopLeft());
			pDC->SelectObject(pp);						//
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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
				sd->ObjectContainDialog.SelectedObjects();//更新ObjectContainDialog
				sd->FunctionDialog()->SetSubDialog();//更新FunctionDialog
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
		//先清除容器內的東西
		isSelecting=false;
		this->UnSelected();
		this->selectedSprites.insert(sprite);
		sprite->OnSelected();
		EraseSprites();
		//最後
	}

	set<CSprite*>& CSelectionPanel::SelectedSprites(){
		return selectedSprites;
	}


	void OnShowSelectedLine(){
		
	}

	void CSelectionPanel::OnShowHPLine(){
		set<CSprite*>::iterator it;
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
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
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		//if(isSelected){
		//	//畫圓圈
		//	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
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
		//	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		//}
	}
	

}