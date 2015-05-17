#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CBuildingBuilder.h"
#include "mygame.h"

#include "CBuildTownCenter.h"
#include "CResourceCenter.h"
#include "CTownCenter.h"

namespace game_framework {
	CBuildTownCenter::CBuildTownCenter()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_TOWNCENTER);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/TownCenter.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(250,0,100,50);
	}
	CBuildTownCenter::~CBuildTownCenter(){icon=NULL;}

	void CBuildTownCenter::Build()
	{
		CBuildingBuilder* buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
		CBuilding* building = new CTownCenter();
		building->SetHP(1);
		building->SetPlayer(sprite->Player());
		buildingBuilder->SetBuilding(building);
	}
}