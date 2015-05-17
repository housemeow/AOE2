#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "mygame.h"
#include "CTownCenter.h"
#include "CBuildTownCenter.h"
#include "CBuildVillager.h"
#include "mygame.h"

namespace game_framework {
	CTownCenter::CTownCenter(){
		spendResource = CResourceTable(250,0,100,50);
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_BUILDING_TOWNCENTER);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_TOWNCENTER);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Building/TownCenter.bmp",0);
		//icon=new CMovingBitmap();

		viewDistance = 15;
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/TownCenter.bmp",-1);
		iconDialog.pic=*icon;
		hp = 100;
		this->maxHp = 100;
		gridSize = CSize(6,6);
	}
	CTownCenter::~CTownCenter(){

		bmp = icon = NULL;
	}
	
	void CTownCenter::FunctionDialogComposite(){
		if(isComplete){
			CScreenDialog* sd = CScreenDialog::GetScreenDialog();
			CBuildVillager* bv = new CBuildVillager();
			bv->SetSprite(this);
			sd->FunctionDialog()->AddSubDialog(bv);
		}
	}

	
	void CTownCenter::PlaySelectedSound(){
		CAudio::Instance()->Play(AUDIO_TOWN,false);
	}
}