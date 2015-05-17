#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CStable.h"
#include "CBuildKnight.h"
#include "mygame.h"

namespace game_framework {
	CStable::CStable(){
		spendResource = CResourceTable(200,0,0,0);
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_BUILDING_STABLE);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_STABLE);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Building/Stable.bmp",0);
		//icon=new CMovingBitmap();

		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/Stable.bmp",-1);
		iconDialog.pic=*icon;
		hp = 150;
		this->maxHp = 150;
		gridSize = CSize(4,4);
	}
	CStable::~CStable(){
		bmp = icon = NULL;
	}
	
	void CStable::FunctionDialogComposite(){
		if(isComplete){
			CScreenDialog* sd = CScreenDialog::GetScreenDialog();
			CBuildKnight* bsm = new CBuildKnight();
			bsm->SetSprite(this);
			sd->FunctionDialog()->AddSubDialog(bsm);
		}
	}
	
	void CStable::PlaySelectedSound(){
		CAudio::Instance()->Play(AUDIO_STABLE,false);
	}
}