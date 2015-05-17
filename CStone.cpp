#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CSprite.h"
#include "CResource.h"
#include "CStone.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 石頭的class
/////////////////////////////////////////////////////////////////////////////

	CStone::CStone(){
		resourceTable = CResourceTable(0,0,0,1);
		bmp = new CMovingBitmap();
		bmp->LoadBitmapA("Bitmaps/Resource/stone.bmp",0);
		icon=new CMovingBitmap();
		icon->LoadBitmapA("Bitmaps/Icons/Units/stone.bmp",-1);
		iconDialog.pic=*icon;
		hp = 100;
		this->maxHp = 100;
		isAttackable = false;
		isCollectable=true;
		isRepairable=false;
	}
	CStone::~CStone(){
		delete bmp;
		delete icon;
	}
	void CStone::OnCollected(CSprite* sprite){//子類別需要給指定的
		hp-=1;
		if(hp<=0){
			this->OnDie();
		}
	}			
}