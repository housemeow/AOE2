#ifndef CVILLAGER_H
#define CVILLAGER_H
#include "CUnit.h"


namespace game_framework {
	////
	////CVillager
	////
	class CVillager:public CUnit{
	public:
		CVillager();
		~CVillager();
		void Collect();
		void Repair();
		void FunctionDialogComposite();
	private:
	};
}
#endif