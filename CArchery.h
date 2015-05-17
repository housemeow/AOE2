#ifndef CARCHERY_H
#define CARCHERY_H

#include "CBuilding.h"
namespace game_framework {
	////
	////CArchery
	////
	class CArchery:public CBuilding{
	public:
		CArchery();
		~CArchery();
		void FunctionDialogComposite();
		void PlaySelectedSound();
	private:
	};
}
#endif