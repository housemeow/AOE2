#ifndef CPLAYER_H
#define CPLAYER_H

#include <set>
#include "CSprite.h"
#include "CResourceTable.h"

namespace game_framework {
	////
	////CPlayer
	////
	class CSprite;
	class CPlayer{
	public:
		CPlayer();
		~CPlayer();
		set<CSprite*>& Sprites();
		void AddDieSprite(CSprite* sprite);
		void EraseSprites();
		static CPlayer* GetPlayer();
		static CPlayer* GetNPC();
		static CPlayer* GetNature();
		static void Dispose();
		CResourceTable& ResourceTable();
		void ShowBitmap(CPoint screenPoint);
	private:
		static CPlayer* player;
		static CPlayer* npc;
		static CPlayer* nature;
		set<CSprite*> sprites;
		set<CSprite*> dieSprites;
		CResourceTable resourceTable;
		CMovingBitmap mark;
	};
}
#endif