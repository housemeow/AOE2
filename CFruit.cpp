#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CSprite.h"
#include "CResource.h"
#include "CFruit.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 果樹叢的class
/////////////////////////////////////////////////////////////////////////////

	CFruit::CFruit(){
		resourceTable = CResourceTable(0,1,0,0);
		bmp = new CMovingBitmap();
		bmp->LoadBitmapA("Bitmaps/Resource/fruit.bmp",0);
		icon=new CMovingBitmap();
		icon->LoadBitmapA("Bitmaps/Icons/Units/fruit.bmp",-1);
		iconDialog.pic=*icon;
		hp = 150;
		this->maxHp = 150;
		isAttackable = false;
		isCollectable=true;
		isRepairable=false;
	}
	CFruit::~CFruit(){
		delete bmp;
		delete icon;
	}
	void CFruit::OnCollected(CSprite* sprite){//子類別需要給指定的
		hp-=1;
		if(hp<=0){
			this->OnDie();
		}
	}			
}