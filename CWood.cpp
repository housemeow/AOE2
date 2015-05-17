#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CSprite.h"
#include "CResource.h"
#include "CWood.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 木頭的class
/////////////////////////////////////////////////////////////////////////////

	CWood::CWood(){
		resourceTable = CResourceTable(1,0,0,0);
		bmp = new CMovingBitmap();
		bmp->LoadBitmapA("Bitmaps/Resource/wood.bmp",0);
		icon=new CMovingBitmap();
		icon->LoadBitmapA("Bitmaps/Icons/Units/wood.bmp",-1);
		iconDialog.pic=*icon;
		hp = 100;
		this->maxHp = 100;
		isAttackable = false;
		isCollectable=true;
		isRepairable=false;
	}
	CWood::~CWood(){
		delete bmp;
		delete icon;
	}
	void CWood::OnCollected(CSprite* sprite){//子類別需要給指定的
		hp-=1;
		if(hp<=0){
			this->OnDie();
		}
	}			
}