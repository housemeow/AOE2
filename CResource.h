#ifndef CRESOURCE_H
#define CRESOURCE_H

#include "CSprite.h"

namespace game_framework {
	class CResource: public CSprite{
	public:
		CResource();
		void OnSelected();			//�n�B�z�A��ܮؤ��u�X�{�@�������p
		void OnShowSelectedLine();
		//void SetMapPoint(CPoint mapPoint);
		void FitMapPoint(CPoint mapPoint);
	};
}
#endif