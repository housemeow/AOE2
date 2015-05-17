#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CBuildingBuilder.h"
#include "CBuildArchery.h"
#include "CArchery.h"

namespace game_framework {
	CBuildArchery::CBuildArchery()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_ARCHERY);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/archery.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(150,0,0,0);
	}
	CBuildArchery::~CBuildArchery(){icon=NULL;}

	void CBuildArchery::Build()
	{
		CBuildingBuilder* buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
		CBuilding* building = new CArchery();
		building->SetHP(1);
		building->SetPlayer(sprite->Player());
		buildingBuilder->SetBuilding(building);
	}
}