#ifndef CARCHER_H
#define CARCHER_H
#include "CUnit.h"


namespace game_framework {
	////
	////CArcher
	////
	class CArcher:public CUnit{
	public:
		CArcher();
		~CArcher();
		void OnMove();
		void OnShow();
		void SetArrowTopLeft(CPoint point);
	private:
		CMovingBitmap arrow;
		CPoint arrowMapPoint;
	};
}
#endif