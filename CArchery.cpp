#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CArchery.h"
#include "CBuildArcher.h"
#include "mygame.h"

namespace game_framework {
	CArchery::CArchery(){
		spendResource = CResourceTable(150,0,0,0);
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_BUILDING_ARCHERY);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_ARCHERY);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Building/archery.bmp",0);

		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/archery.bmp",-1);
		iconDialog.pic=*icon;
		hp = 150;
		this->maxHp = 150;
		gridSize = CSize(4,4);
	}
	CArchery::~CArchery(){
		bmp = icon = NULL;
	}
	
	void CArchery::FunctionDialogComposite(){
		if(isComplete){
			CScreenDialog* sd = CScreenDialog::GetScreenDialog();
			CBuildArcher* ba = new CBuildArcher();
			ba->SetSprite(this);
			sd->FunctionDialog()->AddSubDialog(ba);
		}
	}

	void CArchery::PlaySelectedSound(){
		CAudio::Instance()->Play(AUDIO_ARCHERY,false);
	}
}