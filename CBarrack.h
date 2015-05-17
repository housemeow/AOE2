#ifndef CBARRACK_H
#define CBARRACK_H

#include "CBuilding.h"
namespace game_framework {
	////
	////CBarrack
	////
	class CBarrack:public CBuilding{
	public:
		CBarrack();
		~CBarrack();
		void FunctionDialogComposite();
		void PlaySelectedSound();
	private:
	};
}
#endif