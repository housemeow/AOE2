#ifndef CBUILDING_H
#define CBUILDING_H

#include "CSprite.h"

namespace game_framework {
	////
	////CBuilding
	////
	class CBuilding:public CSprite{
	public:
		CBuilding();
		~CBuilding();
		void OnSelected();
		void OnShowSelectedLine();
		void FitMapPoint(CPoint mapPoint);
		void OnRepaired(CSprite* sprite);
		void SetHP(int hp);
		void SetComplete(bool complete);
	private:
	protected:
		bool isComplete;
	};
}
#endif