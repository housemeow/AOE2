#ifndef CFRUIT_H
#define CFRUIT_H

#include "CResource.h"

namespace game_framework {
	class CFruit: public CResource{
	public:
		CFruit();
		~CFruit();
		void OnCollected(CSprite* sprite);			//�l���O�ݭn�����w��
	};
}
#endif