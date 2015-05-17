#ifndef CGAMEDIALOG_H
#define CGAMEDIALOG_H
#include "CMouseState.h"
namespace game_framework {
	class CGameDialog:public CRect
	{
	public:
		virtual void LoadBitmap(){}
		virtual void OnMove(){}
		virtual void OnShow();
		virtual void Command(){}
		virtual void OnLeftDown(const CMouseState& state){}
		virtual void OnLeftUp(const CMouseState& state){}
		virtual void OnRightDown(const CMouseState& state){}
		virtual void OnRightUp(const CMouseState& state){}
		virtual void OnMouseMove(const CMouseState& state){}
	protected:
		  CMovingBitmap bmp;
	};
}
#endif