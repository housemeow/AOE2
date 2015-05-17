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
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
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
		player=NULL;				//���ݪ��a

		targetRange=0;				//�Ĩ��u�ê��A�ɪ���w�d��

		atkGridRange=0;				//�����Z��
		atkSpeed=0;					//�����t��
		atkCount=0;
		atkUnit=0;					//�����@���쪺�����O
		atkSwordman=0;				//�����C�h�������O
		atkArcher=0;				//�����}�b�⪺�����O
		atkSpearman=0;				//�����٧L�������O
		atkKnight=0;					//�����M�h�������O
		def=0;						//���m�O
		
		direct=0;					//�ثe����
		moveSpeed=0;				//���ʳt��
		viewDistance=0;				//�����Z��
	
		collectSpeed=0;				//�Ķ��t��
		collectCount=0;				//�Ķ��p�ƾ�
		repairCount=0;

		bmp=NULL;		//�ثe��ܦAGameMap���Ϥ��A�ǥ�Animator�����
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
		//	//�Ŧ�����
		//	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
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
		//	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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


	int CSprite::FindXAxis(int left,int right,int y){////��X�b������(�Hy���D)
		CGameMap* map = CGameMap::GetMap();
		for(int x=left;x<=right;x++){
			CPoint point(x,y);
			if(!map->GridRect().PtInRect(point)){//�u��b�a�Ϥ���MapTile
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

	

	int CSprite::FindYAxis(int top,int bottom,int x){//��Y�b������(�Hx���D))
		CGameMap* map = CGameMap::GetMap();
		for(int y=top;y<=bottom;y++){
			CPoint point(x,y);
			if(!map->GridRect().PtInRect(point)){//�u��b�a�Ϥ���MapTile
				continue;
			}
			CMapTile* mapTile = map->GetMapTile(point);
			set<CSprite*>::iterator it;
			for(it=mapTile->Sprites().begin();it!=mapTile->Sprites().end();it++){
				CTarget target(*it);
				if(target.IsAttackable(this)){
					if(this->target.IsSprite()){//�M�����e��w�����
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
			//�q�ۨ��}�l���~�X�i
			CRect rect(this->GridRect());
			for(int i=0;i< this->targetRange;i++){
				rect.InflateRect(0,0,0,1);//���U+1�M��qbottom�}�l�j�M
				if(FindXAxis(rect.left,rect.right,rect.bottom)){//�p�G���h���X
					return;
				}
				rect.InflateRect(0,0,1,0);//���k+1�M��qright�}�l�j�M
				if(FindYAxis(rect.top,rect.bottom,rect.right)){//�p�G���h���X
					return;
				}
				rect.InflateRect(0,1,0,0);//���W+1�M��qtop�}�l�j�M
				if(FindXAxis(rect.left,rect.right,rect.top)){//�p�G���h���X
					return;
				}
				rect.InflateRect(1,0,0,0);//����+1�M��qleft�}�l�j�M
				if(FindYAxis(rect.top,rect.bottom,rect.left)){//�p�G���h���X
					return;
				}
			}
		}
	}

	void CSprite::OnDie(){
		set<CSprite*>::iterator it;
		//�����Ҧ���w�ۤv��Sprite
		if(target.IsSprite()){
			target.Sprite()->targetedSprites.erase(this);
		}
		for(it=targetedSprites.begin();it!=targetedSprites.end();it++){
			(*it)->SetTarget(CTarget::Null());
		}
		//�M���P�a�O�����p
		ClearMapTile();
		ClearVisionCount();
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		//�M������ؤ�������
		panel->AddSpriteToEraseQueue(this);
		//�q���ݪ��a����
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
			if(target.IsSprite()){//�ۤv��w���ؼлݸ��軡�n������w
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
		if(target.Sprite()!=this){//������w�ۤv
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
