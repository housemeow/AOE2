#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildingBuilder.h"
#include "CBuildArcher.h"
#include "CArcher.h"

namespace game_framework {

	CBuildArcher::CBuildArcher()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_ARCHER);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/archer.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(50,0,20,0);
	}
	CBuildArcher::~CBuildArcher(){icon=NULL;}

	void CBuildArcher::Build(){
		CArcher* v = new CArcher();
		v->SetPlayer(sprite->Player());
		v->SetMapPointAndMapTile(sprite->MapPoint() +CPoint(64,64));
		v->SetVisionCount();
		v->SetTarget(this->sprite->Target());
	}
}