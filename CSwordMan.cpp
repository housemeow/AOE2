#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CResourceCenter.h"
#include "CUnit.h"
#include "CDialog.h"
#include "CSwordman.h"
#include "mygame.h"

namespace game_framework {
	
	CSwordman::CSwordman(){
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_UNITS_SWORDMAN);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_SWORDMAN);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Sprites/Units/Swordman/swordman.bmp",0);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/swordman.bmp",-1);
		iconDialog.pic=*icon;
		moveSpeed=5;
		atkSpeed = 50;
		atkUnit = 5;
		atkGridRange = 1;
		targetRange = 5;
		hp = 50;
		this->maxHp = 50;
		isAttackable = true;
		isCollectable=false;
		isRepairable=false;
	}
	CSwordman::~CSwordman(){
		bmp=NULL;
		icon=NULL;
	}
	
}