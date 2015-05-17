#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CResourceCenter.h"
#include "CUnit.h"
#include "CDialog.h"
#include "CKnight.h"
#include "mygame.h"

namespace game_framework {
	
	CKnight::CKnight(){

		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_UNITS_KNIGHT);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_KNIGHT);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Sprites/Units/Knight/knight.bmp",0);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/knight.bmp",-1);
		iconDialog.pic=*icon;
		moveSpeed=12;
		atkSpeed = 25;
		atkUnit = 6;
		atkGridRange=1;
		targetRange = 5;
		hp = 70;
		this->maxHp = 70;
		isAttackable = true;
		isCollectable=false;
		isRepairable=false;
	}
	CKnight::~CKnight(){
		bmp=NULL;
		icon=NULL;
	}
	
}