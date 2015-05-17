#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildingBuilder.h"
#include "CBuildSwordMan.h"
#include "CSwordMan.h"

namespace game_framework {
	CBuildSwordMan::CBuildSwordMan()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_SWORDMAN);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/swordman.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(0,60,20,0);
	}
	CBuildSwordMan::~CBuildSwordMan(){icon=NULL;}

	void CBuildSwordMan::Build(){
		CSwordman* v = new CSwordman();
		v->SetPlayer(sprite->Player());
		v->SetMapPointAndMapTile(sprite->MapPoint() +CPoint(64,64));
		v->SetVisionCount();
		v->SetTarget(this->sprite->Target());
	}
}