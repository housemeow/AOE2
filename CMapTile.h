#ifndef CMAPTILE_H
#define CMAPTILE_H

#include "CSprite.h"
#include <set>

namespace game_framework {
	////
	////CMapTile
	////
	/*
	一個MapTile內部有2*2的的格子，用來放CObject
	*/
	class CMapTile{
	public:
		static enum Tile{
			GREEN,BROWN,RED,BLACK,TILE_COUNT
		};
		~CMapTile();
		CMapTile();
		CMapTile(CPoint);
		void SetTile(Tile);
		void SetPoint(CPoint);
		Tile GetTile();
		void static LoadBitmap();
		void static ReleaseBitmap();
		void OnShow();
		void OnShowSprites();
		static const int MH,MW;
		bool IsEmpty();
		set<CSprite*>& Sprites();
		bool& IsExplored();
		int& VisionCount();
	private:
		Tile tile;
		CPoint gridPoint;
		static CMovingBitmap *bitmap[50];
		static bool isLoaded;
		bool isExplored;
		int  visionCount;
		set<CSprite*> sprites;
	};
}
#endif