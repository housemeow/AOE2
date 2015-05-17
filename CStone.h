#ifndef CSTONE_H
#define CSTONE_H

#include "CResource.h"

namespace game_framework {
	class CStone: public CResource{
	public:
		CStone();
		~CStone();
		void OnCollected(CSprite* sprite);			//子類別需要給指定的
	};
}
#endif