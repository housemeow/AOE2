#ifndef CMOUSESTATE_H
#define CMOUSESTATE_H

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class儲存滑鼠資訊
/////////////////////////////////////////////////////////////////////////////
	class CMouseState{
	public:
		bool LeftIsDown();
		bool RightIsDown();
		CPoint LeftDownPoint();
		CPoint RightDownPoint();
		CPoint NowPoint();
		void SetLeftIsDown(const bool& isDown);
		void SetRightIsDown(const bool& isDown);
		void SetLeftDownPoint(const CPoint& point);
		void SetRightDownPoint(const CPoint& point);
		void SetNowPoint(const CPoint& point);
	private:
		bool leftIsDown;
		bool rightIsDown;
		CPoint leftDownPoint;
		CPoint rightDownPoint;
		CPoint nowPoint;
	};
}
#endif