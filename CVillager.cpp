#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CResourceCenter.h"
#include "CUnit.h"
#include "CDialog.h"
#include "CVillager.h"
#include "CBuildStable.h"
#include "CBuildTownCenter.h"
#include "CBuildBarrack.h"
#include "CBuildArchery.h"
#include "mygame.h"

namespace game_framework {
	CVillager::CVillager(){
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_UNITS_VILLAGER);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_VILLAGER);

		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Sprites/Units/Villager/villager.bmp",0);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/villager_male.bmp",-1);
		iconDialog.pic=*icon;
		moveSpeed=8;
		atkSpeed = 30;
		atkGridRange=1;
		hp = 25;
		this->maxHp = 25;
		targetRange = 5;
		isAttackable = true;
		isCollectable=false;
		isRepairable=false;
	}
	CVillager::~CVillager(){
		bmp=NULL;
		icon=NULL;
	}
	
	void CVillager::Collect(){
		if(collectCount++>=20){
			collectCount=0;
			CResourceTable table = target.Sprite()->ResourceTable();
			resourceTable = resourceTable+table;
			player->ResourceTable() += table;
			target.Sprite()->OnCollected(this);
		}
	}
	void CVillager::Repair(){
		if(repairCount++>=20){
			repairCount=0;
			target.Sprite()->OnRepaired(this);
		}
	}

	void CVillager::FunctionDialogComposite()
	{
		CScreenDialog* sd = CScreenDialog::GetScreenDialog();

		CBuildTownCenter* btc = new CBuildTownCenter();
		btc->SetSprite(this);
		sd->FunctionDialog()->AddSubDialog(btc);

		CBuildBarrack* bb = new CBuildBarrack();
		bb->SetSprite(this);
		sd->FunctionDialog()->AddSubDialog(bb);

		CBuildStable* bs = new CBuildStable();
		bs->SetSprite(this);
		sd->FunctionDialog()->AddSubDialog(bs);

		CBuildArchery* ba = new CBuildArchery();
		ba->SetSprite(this);
		sd->FunctionDialog()->AddSubDialog(ba);
		TRACE("V\n");
	}
}