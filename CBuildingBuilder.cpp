#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "CTownCenter.h"
#include "CConvert.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為蓋房子專用的類別，管理尚未放至於地圖上的房子，
/////////////////////////////////////////////////////////////////////////////
	CBuildingBuilder* CBuildingBuilder::buildingBuilder=NULL;
	CBuildingBuilder* CBuildingBuilder::GetBuildingBuilder(){
		if(buildingBuilder==NULL){
			buildingBuilder = new CBuildingBuilder();
		}
		return buildingBuilder;
	}
	void CBuildingBuilder::ReleaseBuildingBuilder(){
		delete buildingBuilder;
		buildingBuilder = NULL;
	}

	CBuildingBuilder::CBuildingBuilder(){
		building = NULL;
	}
	CBuildingBuilder::~CBuildingBuilder(){
		if(building){
			building->OnDie();
		}
		building=NULL;
	}
	
	bool CBuildingBuilder::IsBuilding(){
		return building!=NULL;
	}

	void CBuildingBuilder::SetBuilding(CBuilding* building){
		if(this->building!=NULL){
			this->building->Player()->AddDieSprite(this->building);
			CSelectionPanel::GetSelectionPanel()->AddSpriteToEraseQueue(this->building);
			//this->building->SetVisionCount();
			//this->building->OnDie();
		}
		this->building = building;
	}

	void CBuildingBuilder::PutBuilding(){
		CRect rect = building->GridRect();
		CGameMap* map = CGameMap::GetMap();
		if(map->CanPutHere(rect)){
			CPoint mapPoint(CConvert::GetMapPointByScreenPoint(CMouse::GetMouse()->Point()));
			building->SetMapPointAndMapTile(mapPoint);
			building->SetVisionCount();
			CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();//設定所有選取物件鎖定這個建築物
			set<CSprite*>::iterator it;
			for(it = panel->SelectedSprites().begin();it!=panel->SelectedSprites().end();it++){
				if((*it)->Target().IsSprite()){//清除之前鎖定的單位
					(*it)->Target().Sprite()->targetedSprites.erase(*it);
				}
				(*it)->SetTarget(CTarget(building));
			}
			building = NULL;
		}else{
			CancelBuilding();
		}
	}
	
	void CBuildingBuilder::CancelBuilding(){
		//補回資源
		CPlayer::GetPlayer()->ResourceTable() += building->spendResource;
		SetBuilding(NULL);
	}

	void CBuildingBuilder::OnMove(){
		if(building!=NULL){
			CMouse* mouse = CMouse::GetMouse();
			CPoint gridPoint = CConvert::GetGridPointByScreenPoint(mouse->Point());
			building->SetMapPoint(CConvert::GetMapPointByGridPoint(gridPoint)+CPoint(63,63));
		}
	}

	void CBuildingBuilder::OnShow(){
		if(building!=NULL){
			building->OnShowSelectedLine();
			building->OnShow();
		}
	}
}