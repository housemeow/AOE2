#ifndef CTOWNCENTER_H
#define CTOWNCENTER_H

#include "CBuilding.h"
namespace game_framework {
	////
	////CTownCenter
	////
	class CTownCenter:public CBuilding{
	public:
		CTownCenter();
		~CTownCenter();
		void FunctionDialogComposite();
		void PlaySelectedSound();
	private:
	};
}
#endif