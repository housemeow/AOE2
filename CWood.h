#ifndef CWOOD_H
#define CWOOD_H

#include "CResource.h"

namespace game_framework {
	class CWood: public CResource{
	public:
		CWood();
		~CWood();
		void OnCollected(CSprite* sprite);			//�l���O�ݭn�����w��
	};
}
#endif