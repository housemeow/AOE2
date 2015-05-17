#ifndef CMOUSE_H
#define CMOUSE_H

#include "CMouseState.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��singleton class���ѷƹ������A�ݪ��D�U�Өƥ󪺨ϥήɾ�
// 
/////////////////////////////////////////////////////////////////////////////
	class CMouse{
	public:
		//���o�ƹ�����
		static CMouse* GetMouse();
		//����ƹ�����
		void Dispose();
		//�ƹ��ƥ�
		void OnLeftDown(const CPoint&);
		void OnLeftUp(const CPoint&);
		void OnLeftClick(const CPoint&);
		void OnRightDown(const CPoint&);
		void OnRightUp(const CPoint&);
		void OnRightClick(const CPoint&);
		void OnMouseMove(const CPoint&);
		//�ƹ����A
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