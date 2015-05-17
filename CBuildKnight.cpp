#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildingBuilder.h"
#include "CBuildKnight.h"
#include "CKnight.h"

namespace game_framework {

	CBuildKnight::CBuildKnight()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_KNIGHT);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Units/knight.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(0,70,50,0);
	}
	CBuildKnight::~CBuildKnight(){icon=NULL;}


	void CBuildKnight::Build(){
		CKnight* v = new CKnight();
		v->SetPlayer(sprite->Player());
		v->SetMapPointAndMapTile(sprite->MapPoint() +CPoint(64,64));
		v->SetVisionCount();
		v->SetTarget(this->sprite->Target());
	}
}