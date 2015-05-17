#ifndef CSTABLE_H
#define CSTABLE_H

#include "CBuilding.h"
namespace game_framework {
	////
	////CStable
	////
	class CStable:public CBuilding{
	public:
		CStable();
		~CStable();
		void FunctionDialogComposite();
		void PlaySelectedSound();
	private:
	};
}
#endif