#ifndef CUNIT_H
#define CUNIT_H

#include "CSprite.h"
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class是可移動的單位，衍生類別有CVillager、CSwordMan、CSpearMan
// 衍生類別需初始atk、def、hp、speed、atkDelay、atkrange
// isAttackable、isCollectable、isRepairable變數
/////////////////////////////////////////////////////////////////////////////
	class CUnit:public CSprite{
	public:
		CUnit();
		~CUnit();
		void OnMove();//移動的Function
		void Attack();
		void OnShowSelectedLine();
	private:
		void Move(const CPoint &newMapPoint);
		int idleCount;
	};
}
#endif