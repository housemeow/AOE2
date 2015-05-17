#ifndef CMOUSE_H
#define CMOUSE_H

#include "CMouseState.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個singleton class提供滑鼠介面，需知道各個事件的使用時機
// 
/////////////////////////////////////////////////////////////////////////////
	class CMouse{
	public:
		//取得滑鼠實體
		static CMouse* GetMouse();
		//釋放滑鼠實體
		void Dispose();
		//滑鼠事件
		void OnLeftDown(const CPoint&);
		void OnLeftUp(const CPoint&);
		void OnLeftClick(const CPoint&);
		void OnRightDown(const CPoint&);
		void OnRightUp(const CPoint&);
		void OnRightClick(const CPoint&);
		void OnMouseMove(const CPoint&);
		//滑鼠狀態
		CPoint& LeftDownPoint();
		CPoint& RightDownPoint();
		CPoint& Point();
		bool& LeftIsDown();
		bool& RightIsDown();
		bool& MoveAfterMouseDown();
		CMouseState& MouseState();
	private:
		static CMouse* mouse;
		CMouse();
		~CMouse();
		bool leftIsDown;
		bool rightIsDown;
		bool moveAfterMouseDown;
		CPoint point;
		CPoint leftDownPoint;
		CPoint rightDownPoint;
		CMouseState mouseState;
	};


}
#endif