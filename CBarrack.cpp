#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CBarrack.h"
#include "CBuildSwordMan.h"
#include "mygame.h"

namespace game_framework {
	CBarrack::CBarrack(){
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_BUILDING_BARRACK);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_BARRACK);
		spendResource = CResourceTable(150,0,0,0);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Building/Barrack.bmp",0);
		//icon=new CMovingBitmap();

		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/Barrack.bmp",-1);
		iconDialog.pic=*icon;
		hp = 150;
		this->maxHp = 150;
		gridSize = CSize(4,4);
	}
	CBarrack::~CBarrack(){

		bmp = icon = NULL;
	}
	
	void CBarrack::FunctionDialogComposite(){
		if(isComplete){
			CScreenDialog* sd = CScreenDialog::GetScreenDialog();
			CBuildSwordMan* bsm = new CBuildSwordMan();
			bsm->SetSprite(this);
			sd->FunctionDialog()->AddSubDialog(bsm);
		}
	}
	
	void CBarrack::PlaySelectedSound(){
		CAudio::Instance()->Play(AUDIO_BARRACK,false);
	}
}