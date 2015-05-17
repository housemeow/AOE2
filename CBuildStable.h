#ifndef CBUILDSTABLE_H
#define CBUILDSTABLE_H
#include "CBuildDialog.h"
namespace game_framework {
	class CBuildStable:public CBuildDialog			 
	{
	public :
		CBuildStable();
		~CBuildStable();
		void Build();
	};
}

#endif