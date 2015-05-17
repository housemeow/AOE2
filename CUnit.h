#ifndef CUNIT_H
#define CUNIT_H

#include "CSprite.h"
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class�O�i���ʪ����A�l�����O��CVillager�BCSwordMan�BCSpearMan
// �l�����O�ݪ�latk�Bdef�Bhp�Bspeed�BatkDelay�Batkrange
// isAttackable�BisCollectable�BisRepairable�ܼ�
/////////////////////////////////////////////////////////////////////////////
	class CUnit:public CSprite{
	public:
		CUnit();
		~CUnit();
		void OnMove();//���ʪ�Function
		void Attack();
		void OnShowSelectedLine();
	private:
		void Move(const CPoint &newMapPoint);
		int idleCount;
	};
}
#endif