#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMouseState.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CMouseState: �ƹ����A�����O�A������B�k����U���I�P�ثe�ƹ����I�A�٦����k��O�_���U����T
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