#ifndef CRESOURCE_H
#define CRESOURCE_H

#include "CSprite.h"

namespace game_framework {
	class CResource: public CSprite{
	public:
		CResource();
		void OnSelected();			//要處理再選擇框內只出現一次的狀況
		void OnShowSelectedLine();
		//void SetMapPoint(CPoint mapPoint);
		void FitMapPoint(CPoint mapPoint);
	};
}
#endif