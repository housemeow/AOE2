#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMouseState.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CMouseState: 滑鼠狀態的類別，有左鍵、右鍵按下的點與目前滑鼠的點，還有左右鍵是否按下的資訊
/////////////////////////////////////////////////////////////////////////////
	bool CMouseState::LeftIsDown(){return leftIsDown;}
	bool CMouseState::RightIsDown(){return rightIsDown;}
	CPoint CMouseState::LeftDownPoint(){return leftDownPoint;}
	CPoint CMouseState::RightDownPoint(){return rightDownPoint;}
	CPoint CMouseState::NowPoint(){return nowPoint;}
	void CMouseState::SetLeftIsDown(const bool& isDown){leftIsDown = isDown;}
	void CMouseState::SetRightIsDown(const bool& isDown){rightIsDown = isDown;}
	void CMouseState::SetLeftDownPoint(const CPoint& point){leftDownPoint = point;}
	void CMouseState::SetRightDownPoint(const CPoint& point){rightDownPoint = point;}
	void CMouseState::SetNowPoint(const CPoint& point){nowPoint = point;}
}