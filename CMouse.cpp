#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMouse.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "CConvert.h"
#include "CMouse.h"
#include "mygame.h"

namespace game_framework {
	//CScreenDialog *ScreenDialog;
/////////////////////////////////////////////////////////////////////////////
// CMouse: Mouse class
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Singleton class存取與釋放方法
	CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
	CMouse* CMouse::mouse=NULL;
	CMouse* CMouse::GetMouse(){
		if(mouse==NULL){
			mouse = new CMouse();
		}
		return mouse;
	}
	void CMouse::Dispose(){
		delete mouse;
		mouse=NULL;
	}
/////////////////////////////////////////////////////////////////////////////
	
	void CMouse::OnLeftDown(const CPoint&point){
		CStartDialog* startDialog = CStartDialog::GetStartDialog();
		//startDialog->OnLeftDown(this->

		CBuildingBuilder* buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
		if(buildingBuilder->IsBuilding()){
			buildingBuilder->PutBuilding();
		}

		CScreenDialog* sd = CScreenDialog::GetScreenDialog();
		if(sd->MapDialog.PtInRect(point)){//如果左鍵點在地圖上面
			////處理SelectionPanel
			//開始選取動作
			panel->IsSelecting()=true;
			//設定框選預設值
			panel->Rect() = CRect(point,point);
			////SelectionPanel完畢
		}
		CScreenDialog *screenDialog = CScreenDialog::GetScreenDialog();
		if(screenDialog->SmallMapDialog.PtInRect(point)){
			screenDialog->SmallMapDialog.IsLeftMouseDown=true;}
		screenDialog->CheckThePointIn(point);
		//TRACE("OnLeftDown\n");
	}
	void CMouse::OnLeftUp(const CPoint&point){
		////處理SelectionPanel
		//如果SelectionPanel動作中而且有移動 則呼叫OnSelected(框選)
		if(panel->IsSelecting() && moveAfterMouseDown){
			CRect rect(leftDownPoint,point);
			rect.NormalizeRect();
			panel->Rect()=rect;
			panel->OnSelected(panel->Rect());
		}
		//選取動作完畢
		panel->IsSelecting()=false;
		
		////SelectionPanel完畢
		CScreenDialog* screenDialog= CScreenDialog::GetScreenDialog();
		screenDialog->SmallMapDialog.IsLeftMouseDown=false;
		//TRACE("OnLeftUp\n");
		screenDialog->ObjectContainDialog.SelectedObjects();
		screenDialog->FunctionDialog()->SetSubDialog();
	}
	void CMouse::OnLeftClick(const CPoint&point){
		////處理SelectionPanel
		//如果SelectionPanel動作中則呼叫點選事件

		if(panel->IsSelecting()){
			panel->OnClick(point);
			panel->IsSelecting()=false;//選取完畢
		}
		
		CScreenDialog *screenDialog = CScreenDialog::GetScreenDialog();
		screenDialog->MapDialog.CheckThePointIn(point);
		////SelectionPanel完畢
		TRACE("OnLeftClick(%d,%d)\n",point.x,point.y);
	}


	void CMouse::OnRightDown(const CPoint&point){
		TRACE("OnRightDown\n");
		CScreenDialog* screenDialog = CScreenDialog::GetScreenDialog();
		if(screenDialog->MapDialog.PtInRect(point)){//點到視窗正中央
			CTarget target=CTarget::Null();
			CGameMap* map = CGameMap::GetMap();
			CPlayer*player,*npc,*nature;
			player = CPlayer::GetPlayer();
			npc = CPlayer::GetNPC();
			nature = CPlayer::GetNature();
			set<CSprite*>::iterator it;
			for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
				if((*it)->ScreenRect().PtInRect(point)){
					target = CTarget(*it);
					break;
				}
			}
			for(it = npc->Sprites().begin();it!=npc->Sprites().end();it++){
				if((*it)->ScreenRect().PtInRect(point)){
					target = CTarget(*it);
					break;
				}
			}
			for(it = nature->Sprites().begin();it!=nature->Sprites().end();it++){
				if((*it)->ScreenRect().PtInRect(point)){
					target = CTarget(*it);
					break;
				}
			}
			if(target.IsNull()){//沒有點到任何Sprite
				CPoint mapPoint(CConvert::GetMapPointByScreenPoint(point));
				mapPoint.x = mapPoint.x>=map->MapSizeX() ? map->MapSizeX():mapPoint.x;
				mapPoint.x = mapPoint.x<0 ? 0:mapPoint.x;
				mapPoint.y = mapPoint.y>=map->MapSizeY() ? map->MapSizeY():mapPoint.y;
				mapPoint.y = mapPoint.y<0 ? 0:mapPoint.y;
				target = CTarget(mapPoint);
			}
			CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
			for(it = panel->SelectedSprites().begin(); it!=panel->SelectedSprites().end();it++){
				if((*it)->Player()==player){//只可操控自己的角色
					if((*it)->Target().IsSprite()){
						(*it)->Target().Sprite()->targetedSprites.erase(*it);
					}
					(*it)->SetTarget(target);
				}
			}
		}
		screenDialog->SmallMapDialog.CheckThePointIn(point);
	}
	void CMouse::OnRightUp(const CPoint&point){
		TRACE("OnRightUp\n");
	}
	void CMouse::OnRightClick(const CPoint&point){
		//動作，判斷點選的地方是點還是物件
	}
	void CMouse::OnMouseMove(const CPoint&point){
		////處理SelectionPanel
		if(leftIsDown && panel->IsSelecting()){
			CRect rect(leftDownPoint,point);
			rect.NormalizeRect();//正規化矩形
			rect&= CRect(0,24,799,462);//只顯示遊戲地圖視窗的範圍
			panel->Rect()=rect;
			panel->OnSelecting(panel->Rect());
		}
		
		CScreenDialog *screenDialog = CScreenDialog::GetScreenDialog();
		if(leftIsDown && screenDialog->SmallMapDialog.IsLeftMouseDown==true){
			screenDialog->CheckThePointIn(point);
		}
		////SelectionPanel完畢
		//TRACE("OnMouseMove(%d,%d)\n",point.x,point.y);
		static int smallestx=88;
		if(point.y<smallestx){
			smallestx=point.y;
			TRACE("OnMouseMove(%d,%d)\n",point.x,point.y);
		}

		CMovingBitmap bmp;
		
	}


	//滑鼠狀態
	CPoint& CMouse::LeftDownPoint(){
		return leftDownPoint;
	}
	CPoint& CMouse::RightDownPoint(){
		return rightDownPoint;
	}
	CPoint& CMouse::Point(){
		return point;
	}
	bool& CMouse::LeftIsDown(){
		return leftIsDown;
	}
	bool& CMouse::RightIsDown(){
		return rightIsDown;
	}
	
	bool& CMouse::MoveAfterMouseDown(){
		return moveAfterMouseDown;
	}

	CMouseState& CMouse::MouseState(){return mouseState;}


	
	CMouse::CMouse(){
		leftIsDown=false;
		rightIsDown=false;
		moveAfterMouseDown=false;
		point=CPoint(0,0);
		leftDownPoint=CPoint(0,0);
		rightDownPoint=CPoint(0,0);
	}
	CMouse::~CMouse(){}

}