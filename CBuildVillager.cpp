#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildingBuilder.h"
#include "CBuildVillager.h"
#include "CVillager.h"

namespace game_framework {
	CBuildVillager::CBuildVillager()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_VILLAGER);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/villager_male.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(0,50,0,0);
	}
	CBuildVillager::~CBuildVillager(){icon=NULL;}


	void CBuildVillager::Build(){
		CVillager* v = new CVillager();
		v->SetPlayer(sprite->Player());
		v->SetMapPointAndMapTile(sprite->MapPoint() +CPoint(64,64));
		v->SetVisionCount();
		v->SetTarget(this->sprite->Target());
		CAudio::Instance()->Play(AUDIO_READY,false);
	}
}