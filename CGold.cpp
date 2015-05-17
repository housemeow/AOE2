#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CSprite.h"
#include "CResource.h"
#include "CGold.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 金塊的class
/////////////////////////////////////////////////////////////////////////////

	CGold::CGold(){
		resourceTable = CResourceTable(0,0,1,0);
		bmp = new CMovingBitmap();
		bmp->LoadBitmapA("Bitmaps/Resource/gold.bmp",0);
		icon=new CMovingBitmap();
		icon->LoadBitmapA("Bitmaps/Icons/Units/gold.bmp",-1);
		iconDialog.pic=*icon;
		hp = 100;
		this->maxHp = 100;
		isAttackable = false;
		isCollectable=true;
		isRepairable=false;
	}
	CGold::~CGold(){
		delete bmp;
		delete icon;
	}
	void CGold::OnCollected(CSprite* sprite){//子類別需要給指定的
		hp-=1;
		if(hp<=0){
			this->OnDie();
		}
	}			
}