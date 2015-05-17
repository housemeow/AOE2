#ifndef CSELECTIONPANEL_H
#define CSELECTIONPANEL_H

#include <set>
#include "CSprite.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��singleton class���ѿ�����Ϋؿv�A
// ���I��P�ؿ蠟�t�O
//
//					OnStartSelected(�g��CMouse::OnLeftDownĲ�o)
//						moved=false;
//							|
//				-------------------------
//				|(OnSelecting)			|(OnClick)
//				|moved=true				|
//				|(�g��MouseMoveĲ�o)	|(�g��LeftClickĲ�o)
//				v						v
//			OnSelected()			OnClick()
//
/////////////////////////////////////////////////////////////////////////////
	class CSelectionPanel{
	public:
		static CSelectionPanel* GetSelectionPanel();
		static void Dispose();

		void OnClick(const CPoint&);					//�I��
		void OnSelecting(const CRect&);					//
		void OnSelected(const CRect&);					//�ؿ�
		void UnSelected();								//�������
		//�ݩ�
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