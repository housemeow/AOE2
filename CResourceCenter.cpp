#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMouse.h"
#include "CResourceCenter.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CConvert.h"
#include "mygame.h"

namespace game_framework 
{
	CBitmapCollection* CBitmapCollection::bitmapCollection=NULL;

	CMovingBitmap* CBitmapCollection::GetBitmap(BITMAP_ID id)
	{
		return bitmaps[id];
	}
	CBitmapCollection::CBitmapCollection()
	{
		for(int i=0;i<BITMAP_ID_COUNT;i++){
			bitmaps[(BITMAP_ID)i] = new CMovingBitmap();
		}
		bitmaps[SPRITES_UNITS_ARCHER]->LoadBitmapA("Bitmaps/Sprites/Units/Archer/archer.bmp",0);
		bitmaps[SPRITES_UNITS_KNIGHT]->LoadBitmapA("Bitmaps/Sprites/Units/Knight/knight.bmp",0);
		bitmaps[SPRITES_UNITS_VILLAGER]->LoadBitmapA("Bitmaps/Sprites/Units/Villager/villager.bmp",0);
		bitmaps[SPRITES_UNITS_SWORDMAN]->LoadBitmapA("Bitmaps/Sprites/Units/Swordman/swordman.bmp",0);
		bitmaps[SPRITES_BUILDING_ARCHERY]->LoadBitmapA("Bitmaps/Sprites/Buildings/Archery.bmp",0);
		bitmaps[SPRITES_BUILDING_BARRACK]->LoadBitmapA("Bitmaps/Sprites/Buildings/Barrack.bmp",0);
		bitmaps[SPRITES_BUILDING_STABLE]->LoadBitmapA("Bitmaps/Sprites/Buildings/Stable.bmp",0);
		bitmaps[SPRITES_BUILDING_TOWNCENTER]->LoadBitmapA("Bitmaps/Sprites/Buildings/TownCenter.bmp",0);
		bitmaps[SPRITES_RESOURCE_GOLD]->LoadBitmapA("Bitmaps/Sprites/Resources/gold.bmp",0);
		bitmaps[SPRITES_RESOURCE_FRUIT]->LoadBitmapA("Bitmaps/Sprites/Resources/fruit.bmp",0);
		bitmaps[SPRITES_RESOURCE_STONE]->LoadBitmapA("Bitmaps/Sprites/Resources/stone.bmp",0);
		bitmaps[SPRITES_RESOURCE_WOOD]->LoadBitmapA("Bitmaps/Sprites/Resources/wood.bmp",0);
		bitmaps[ICON_UNITS_ARCHER]->LoadBitmapA("Bitmaps/Icons/Units/archer.bmp",-1);
		bitmaps[ICON_UNITS_KNIGHT]->LoadBitmapA("Bitmaps/Icons/Units/knight.bmp",-1);
		bitmaps[ICON_UNITS_VILLAGER]->LoadBitmapA("Bitmaps/Icons/Units/villager.bmp",-1);
		bitmaps[ICON_UNITS_SWORDMAN]->LoadBitmapA("Bitmaps/Icons/Units/swordman.bmp",-1);
		bitmaps[ICON_BUILDING_ARCHERY]->LoadBitmapA("Bitmaps/Icons/Buildings/archery.bmp",-1);
		bitmaps[ICON_BUILDING_BARRACK]->LoadBitmapA("Bitmaps/Icons/Buildings/Barrack.bmp",-1);
		bitmaps[ICON_BUILDING_STABLE]->LoadBitmapA("Bitmaps/Icons/Buildings/Stable.bmp",-1);
		bitmaps[ICON_BUILDING_TOWNCENTER]->LoadBitmapA("Bitmaps/Icons/Buildings/TownCenter.bmp",-1);
	}
	CBitmapCollection::~CBitmapCollection()
	{
		for(int i=0;i<BITMAP_ID_COUNT;i++){
			delete bitmaps[(BITMAP_ID)i];
		}
	}
	CBitmapCollection* CBitmapCollection::GetBitmapCollection()
	{
		if(bitmapCollection==NULL)
		{
			bitmapCollection=new CBitmapCollection();
		}
		return bitmapCollection;
	}
	void CBitmapCollection::Dispose(){
		delete bitmapCollection;
		bitmapCollection = NULL;
	}
}