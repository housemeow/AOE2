#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceCenter.h"
#include "CBuildingBuilder.h"
#include "CBuildBarrack.h"
#include "CBarrack.h"

namespace game_framework {
	CBuildBarrack::CBuildBarrack()
	{
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_BUILDING_BARRACK);
		//icon=new CMovingBitmap();
		//icon->LoadBitmapA("Bitmaps/Icons/Buildings/barrack.bmp",-1);
		this->pic=*(icon);
		resourceTable = CResourceTable(150,0,0,0);
	}
	CBuildBarrack::~CBuildBarrack(){icon=NULL;}

	void CBuildBarrack::Build()
	{
		CBuildingBuilder* buildingBuilder = CBuildingBuilder::GetBuildingBuilder();
		CBuilding* building = new CBarrack();
		building->SetHP(1);
		building->SetPlayer(sprite->Player());
		buildingBuilder->SetBuilding(building);
	}
}