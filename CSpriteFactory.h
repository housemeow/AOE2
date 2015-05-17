#ifndef CSPRITEFACTORY_H
#define CSPRITEFACTORY_H

namespace game_framework 
{
	class CSpriteFactory
	{
		virtual CSprite* CreatSprite();
	};

	class CUnitFactory:public CSpriteFactory
	{
		virtual CSprite* CreatSprite();
	};
	class CBuildingFactory:public CSpriteFactory
	{
		virtual CSprite* CreatSprite();
	};
	class CResourceFactory:public CSpriteFactory
	{
		virtual CSprite* CreatSprite();
	};
	class CVillagerFactory:public CUnitFactory
	{
		CSprite* CreatSprite();
	};
	class CTownCenterFactory:public CBuildingFactory
	{
		CSprite* CreatSprite();
	};
	class CFruitFactory:public CResourceFactory
	{
		CSprite* CreatSprite();
	};
}

#endif