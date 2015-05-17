#ifndef CSELECTIONPANEL_H
#define CSELECTIONPANEL_H

#include <set>
#include "CSprite.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個singleton class提供選取單位及建築，
// 有點選與框選之差別
//
//					OnStartSelected(經由CMouse::OnLeftDown觸發)
//						moved=false;
//							|
//				-------------------------
//				|(OnSelecting)			|(OnClick)
//				|moved=true				|
//				|(經由MouseMove觸發)	|(經由LeftClick觸發)
//				v						v
//			OnSelected()			OnClick()
//
/////////////////////////////////////////////////////////////////////////////
	class CSelectionPanel{
	public:
		static CSelectionPanel* GetSelectionPanel();
		static void Dispose();

		void OnClick(const CPoint&);					//點選
		void OnSelecting(const CRect&);					//
		void OnSelected(const CRect&);					//框選
		void UnSelected();								//取消選取
		//屬性
		bool& IsSelecting();
		CRect& Rect();
		void SelectSprite(CSprite* sprite);
		set<CSprite*>& SelectedSprites();
		void AddSpriteToEraseQueue(CSprite* sprite);
		void OnShow();
		void OnShowHPLine();
		//void OnShowSelectedLine();
		void EraseSprites();
	private:
		static CSelectionPanel* panel;
		CSelectionPanel();
		~CSelectionPanel();
		bool isSelecting;
		CRect rect;
		int previousSelectedSpritesSize;
		set<CSprite*> selectedSprites;
		set<CSprite*> eraseSprites;
	};
}
#endif