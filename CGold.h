#ifndef CGOLD_H
#define CGOLD_H

#include "CResource.h"

namespace game_framework {
	class CGold: public CResource{
	public:
		CGold();
		~CGold();
		void OnCollected(CSprite* sprite);			//子類別需要給指定的
	};
}
#endif