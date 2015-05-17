#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CSprite.h"
#include "CConvert.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為所有地圖中單位與建築物的基底類別
/////////////////////////////////////////////////////////////////////////////
	int CSprite::count=0;
	
	CSprite::CSprite():id(count++){
		this->isAttackable=false;
		this->isCollectable=false;
		this->isRepairable=false;
		this->isSelected=false;
		isBuilding = false;
		isUnit = false;
		isResource = false;
		player = NULL;
		hp = 1;
		maxHp=1;
		atkCount=0;
		def = 1;
		targetedSprites.clear();
		iconDialog.sprite=this;

		
		this->target = CTarget::Null();
		targetedSprites.clear();
		mapPoint = CPoint(1000,1000);
		gridSize = CSize(1,1);
		this->isAttackable=false;
		this->isCollectable=false;
		this->isRepairable=false;
		this->isSelected=false;
		hp = 1;
		maxHp=1;
		player=NULL;				//所屬玩家

		targetRange=0;				//採取守衛狀態時的鎖定範圍

		atkGridRange=0;				//攻擊距離
		atkSpeed=0;					//攻擊速度
		atkCount=0;
		atkUnit=0;					//攻擊一般單位的攻擊力
		atkSwordman=0;				//攻擊劍士的攻擊力
		atkArcher=0;				//攻擊弓箭手的攻擊力
		atkSpearman=0;				//攻擊矛兵的攻擊力
		atkKnight=0;					//攻擊騎士的攻擊力
		def=0;						//防禦力
		
		direct=0;					//目前面相
		moveSpeed=0;				//移動速度
		viewDistance=0;				//視野距離
	
		collectSpeed=0;				//採集速度
		collectCount=0;				//採集計數器
		repairCount=0;

		bmp=NULL;		//目前顯示再GameMap的圖片，藉由Animator來顯示
		icon=NULL;
	}
	CSprite::~CSprite(){}
	
	void CSprite::OnShow()
	{
		if(isSelected){
			OnShowSelectedLine();
		}
		OnShowSprite();
		//if(isSelected)
		//	OnShowHPLine();

		//if(this->target.IsSprite()){
		//	//藍色選取框
		//	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		//	
		//	CPen penBlue;
		//	CPen* pOldPen;
		//	penBlue.CreatePen(PS_SOLID,1,RGB(0,0,255));
		//	pOldPen = pDC->SelectObject(&penBlue);
		//	CRect rect;
		//	CSize size = this->target.Sprite()->ScreenRect().Size();
		//	CPoint screenPoint(CConvert::GetScreenPointByMapPoint(target.Sprite()->MapPoint()));
		//	rect.SetRect(	screenPoint.x-size.cx/2-10,
		//					screenPoint.y-25,
		//					screenPoint.x+size.cx/2+10,
		//					screenPoint.y+5);

		//	pDC->MoveTo(rect.TopLeft());				// 
		//	pDC->LineTo(rect.right,rect.top);			//
		//	pDC->LineTo(rect.right,rect.bottom);
		//	pDC->LineTo(rect.left,rect.bottom);
		//	pDC->LineTo(rect.TopLeft());

		//	pDC->SelectObject(pOldPen);						//
		//	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		//}else if(this->target.IsPoint()){
		//	//TRACE("point(%d,%d)\n",target.Point().x,target.Point().y);
		//}
	}
	void CSprite::OnShowSprite(){
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint)-CPoint(bmp->Width()/2,bmp->Height()));
		bmp->SetTopLeft(screenPoint.x,screenPoint.y);
		bmp->ShowBitmap();
		screenPoint = CPoint(CConvert::GetScreenPointByMapPoint(mapPoint)) -CPoint(5,20);
		player->ShowBitmap(screenPoint);
	}

	void CSprite::OnAction(){
		if(target.IsSprite()){
			if(target.IsAttackable(this)){
				if(target.InRange(this,this->atkGridRange)){
					Attack();
				}
			}else{
				atkCount=0;
			}
			if(target.IsCollectable(this)){
				Collect();
			}else{
				collectCount=0;
			}
			if(target.IsRepairable(this)){
				Repair();
			}else{
				repairCount=0;
			}
		}
	}

	void CSprite::OnTargeted(CSprite* sprite){
		targetedSprites.insert(sprite);
	}


	int CSprite::FindXAxis(int left,int right,int y){////找X軸的元素(以y為主)
		CGameMap* map = CGameMap::GetMap();
		for(int x=left;x<=right;x++){
			CPoint point(x,y);
			if(!map->GridRect().PtInRect(point)){//只找在地圖內的MapTile
				continue;
			}
			CMapTile* mapTile = map->GetMapTile(point);
			set<CSprite*>::iterator it;
			for(it=mapTile->Sprites().begin();it!=mapTile->Sprites().end();it++){
				CTarget target(*it);
				if(target.IsAttackable(this)){
					this->SetTarget(target);
					return 1;
				}
			}
		}
		return 0;
	}

	

	int CSprite::FindYAxis(int top,int bottom,int x){//找Y軸的元素(以x為主))
		CGameMap* map = CGameMap::GetMap();
		for(int y=top;y<=bottom;y++){
			CPoint point(x,y);
			if(!map->GridRect().PtInRect(point)){//只找在地圖內的MapTile
				continue;
			}
			CMapTile* mapTile = map->GetMapTile(point);
			set<CSprite*>::iterator it;
			for(it=mapTile->Sprites().begin();it!=mapTile->Sprites().end();it++){
				CTarget target(*it);
				if(target.IsAttackable(this)){
					if(this->target.IsSprite()){//清除之前鎖定的單位
						this->target.Sprite()->targetedSprites.erase(*it);
					}
					this->SetTarget(target);
					return 1;
				}
			}
		}
		return 0;
	}

	void CSprite::FindTarget(){
		if(this->target.IsNull()){
			//從自身開始往外擴展
			CRect rect(this->GridRect());
			for(int i=0;i< this->targetRange;i++){
				rect.InflateRect(0,0,0,1);//往下+1然後從bottom開始搜尋
				if(FindXAxis(rect.left,rect.right,rect.bottom)){//如果找到則跳出
					return;
				}
				rect.InflateRect(0,0,1,0);//往右+1然後從right開始搜尋
				if(FindYAxis(rect.top,rect.bottom,rect.right)){//如果找到則跳出
					return;
				}
				rect.InflateRect(0,1,0,0);//往上+1然後從top開始搜尋
				if(FindXAxis(rect.left,rect.right,rect.top)){//如果找到則跳出
					return;
				}
				rect.InflateRect(1,0,0,0);//往左+1然後從left開始搜尋
				if(FindYAxis(rect.top,rect.bottom,rect.left)){//如果找到則跳出
					return;
				}
			}
		}
	}

	void CSprite::OnDie(){
		set<CSprite*>::iterator it;
		//取消所有鎖定自己的Sprite
		if(target.IsSprite()){
			target.Sprite()->targetedSprites.erase(this);
		}
		for(it=targetedSprites.begin();it!=targetedSprites.end();it++){
			(*it)->SetTarget(CTarget::Null());
		}
		//清除與地板的關聯
		ClearMapTile();
		ClearVisionCount();
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		//清除選取框內的角色
		panel->AddSpriteToEraseQueue(this);
		//從所屬玩家移除
		this->player->AddDieSprite(this);
	}

	void CSprite::OnUnselected(){isSelected=false;}
	void CSprite::OnSelected(){
		isSelected=true;
		this->PlaySelectedSound();
	}

	bool CSprite::IsAttackable(){return isAttackable;}
	bool CSprite::IsCollectable(){return isCollectable;}
	bool CSprite::IsRepairable(){return isRepairable;}
	bool CSprite::IsSelected(){return isSelected;}
	bool CSprite::IsBuilding(){return isBuilding;}
	bool CSprite::IsUnit(){return isUnit;}
	bool CSprite::IsResource(){return isResource;}
	
	
	CResourceTable& CSprite::ResourceTable(){
		return resourceTable;}
	int CSprite::HP()const{return hp;}
	int CSprite::AtkGridRange()const{return atkGridRange;}
	int CSprite::MaxHP()const{return maxHp;}
	int CSprite::Atk()const{return atkUnit;}
	int CSprite::Def()const{return def;}

	CRect CSprite::ScreenRect(){
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint)-CPoint(bmp->Width()/2,bmp->Height()));
		CRect rect(screenPoint,CSize(bmp->Width(),bmp->Height()));
		return rect;
	}


	void CSprite::OnAttacked(CSprite* sprite,int damage){
		hp-=damage;
		if(hp<=0){
			hp=0;
			if(target.IsSprite()){//自己鎖定的目標需跟對方說要取消鎖定
				target.Sprite()->targetedSprites.erase(this);
			}
			OnDie();
		}else{
			if(target.IsNull()){
				this->SetTarget(CTarget(sprite));
			}
		}
	}

	void CSprite::SetMapPointAndMapTile(CPoint mapPoint){
		ClearMapTile();
		SetMapPoint(mapPoint);
		FitMapPoint(mapPoint);
		SetMapTile();
	}
	
	void CSprite::SetMapPoint(CPoint mapPoint){
		this->mapPoint = mapPoint;
	}

	void CSprite::SetMapTile(){
		CGameMap* map = CGameMap::GetMap();
		for(int y=GridRect().top;y<=GridRect().bottom;y++){
			for(int x=GridRect().left;x<=GridRect().right;x++){
				map->GetMapTile(CPoint(x,y))->Sprites().insert(this);
			}
		}
	}

	void CSprite::ClearMapTile(){
		CGameMap* map = CGameMap::GetMap();
		for(int y=GridRect().top;y<=GridRect().bottom;y++){
			for(int x=GridRect().left;x<=GridRect().right;x++){
				map->GetMapTile(CPoint(x,y))->Sprites().erase(this);
			}
		}
	}

	void CSprite::SetVisionCount(){
		if(this->player==CPlayer::GetPlayer()){
			this->SetExplored();
			CGameMap* map = CGameMap::GetMap();
			for(int y=VisionRect().top;y<=VisionRect().bottom;y++){
				for(int x=VisionRect().left;x<=VisionRect().right;x++){
					map->GetMapTile(CPoint(x,y))->VisionCount()++;
				}
			}
		}
	}
	void CSprite::ClearVisionCount(){
		if(this->player==CPlayer::GetPlayer()){
			CGameMap* map = CGameMap::GetMap();
			for(int y=VisionRect().top;y<=VisionRect().bottom;y++){
				for(int x=VisionRect().left;x<=VisionRect().right;x++){
					map->GetMapTile(CPoint(x,y))->VisionCount()--;
				}
			}
		}
	}
	
	void CSprite::SetExplored(){
		if(this->player==CPlayer::GetPlayer()){
			CGameMap* map = CGameMap::GetMap();
			for(int y=VisionRect().top;y<=VisionRect().bottom;y++){
				for(int x=VisionRect().left;x<=VisionRect().right;x++){
					map->GetMapTile(CPoint(x,y))->IsExplored()=true;
				}
			}
		}
	}



	CPoint CSprite::MapPoint(){return mapPoint;}
	
	void CSprite::SetTarget(CTarget target){
		if(target.Sprite()!=this){//不能鎖定自己
			this->target = target;
			if(target.IsSprite()){
				target.Sprite()->OnTargeted(this);
			}
		}
	}
	void CSprite::SetPlayer(CPlayer* player){
		this->player = player;
		player->Sprites().insert(this);
	}



	CPoint CSprite::GridPoint(){
		return CConvert::GetGridPointByMapPoint(mapPoint);
	}
	int CSprite::ID()const{return id;}
	CPlayer* CSprite::Player(){return player;}
	CTarget& CSprite::Target(){
		return target;
	}
	CRect CSprite::GridRect()
	{
		CPoint gridPoint=CConvert::GetGridPointByMapPoint(mapPoint);
		gridPoint=CPoint(gridPoint.x-(gridSize.cx-1),gridPoint.y-(gridSize.cy-1));
		CRect rect(gridPoint,gridSize-CSize(1,1));
		rect.NormalizeRect();
		return rect;
	}
	CRect CSprite::VisionRect(){
		CPoint gridPoint=CConvert::GetGridPointByMapPoint(mapPoint);
		gridPoint=CPoint(gridPoint.x-(gridSize.cx-1),gridPoint.y-(gridSize.cy-1));
		CRect rect(gridPoint,gridSize-CSize(1,1));
		rect.NormalizeRect();
		rect.InflateRect(this->viewDistance,this->viewDistance);
		rect &= CGameMap::GetMap()->GridRect();
		return rect;
	}

	void CSprite::CIconDialog::command()
	{
		CScreenDialog* sd = CScreenDialog::GetScreenDialog();
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		panel->SelectSprite(sd->FunctionDialog()->topselectedObject=sprite);
		TRACE("%d\n",sprite->ID());
	}

	CSprite::CIconDialog* CSprite::IconDialog(){
		return &iconDialog;
	}
}
