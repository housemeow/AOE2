#ifndef CWOOD_H
#define CWOOD_H

#include "CResource.h"

namespace game_framework {
	class CWood: public CResource{
	public:
		CWood();
		~CWood();
		void OnCollected(CSprite* sprite);			//子類別需要給指定的
	};
}
#endif