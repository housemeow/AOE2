#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildStable.h"
#include "CStable.h"

namespace game_framework {
	CBuildStable::CBuildStable()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_STABLE);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/stable.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(200,0,0,0);
	}
	CBuildStable::~CBuildStable(){icon=NULL;}

	void CBuildStable::Build()
	{
		CBuildingBuilder* buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
		CBuilding* building = new CStable();
		building->SetHP(1);
		building->SetPlayer(sprite->Player());
		buildingBuilder->SetBuilding(building);
	}
}