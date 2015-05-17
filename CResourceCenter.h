#ifndef CRESOURCECENTER_H
#define CRESOURCECENTER_H



	enum BITMAP_ID
	{
		SPRITES_UNITS_ARCHER,
		SPRITES_UNITS_KNIGHT,
		SPRITES_UNITS_VILLAGER,
		SPRITES_UNITS_SWORDMAN,
		SPRITES_BUILDING_ARCHERY,
		SPRITES_BUILDING_BARRACK,
		SPRITES_BUILDING_STABLE,
		SPRITES_BUILDING_TOWNCENTER,
		SPRITES_RESOURCE_GOLD,
		SPRITES_RESOURCE_FRUIT,
		SPRITES_RESOURCE_STONE,
		SPRITES_RESOURCE_WOOD,
		ICON_UNITS_ARCHER,
		ICON_UNITS_KNIGHT,
		ICON_UNITS_VILLAGER,
		ICON_UNITS_SWORDMAN,
		ICON_BUILDING_ARCHERY,
		ICON_BUILDING_BARRACK,
		ICON_BUILDING_STABLE,
		ICON_BUILDING_TOWNCENTER,
		BITMAP_ID_COUNT
	};
	enum ANIMATION_ID
	{

	};
namespace game_framework 
{
	class CResourceCenter
	{
		public:
			virtual void LoadResource(){};
			virtual void ReleaseResource(){};
			 CResourceCenter(){};
			 ~CResourceCenter(){};
	};
	class CBitmapCollection:public CResourceCenter
	{
		public:
			static void Dispose();
			static CBitmapCollection* GetBitmapCollection();
			CMovingBitmap* GetBitmap(BITMAP_ID);
		private:
			map<BITMAP_ID,CMovingBitmap*> bitmaps;
			static CBitmapCollection* bitmapCollection;
			CBitmapCollection();
			~CBitmapCollection();
	};
	class CSoundCollection:public CResourceCenter
	{
		
	};
	class CAnimationCollection:public CResourceCenter
	{

	};
}
#endif