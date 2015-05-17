#ifndef CBUILDVILLAGER_H
#define CBUILDVILLAGER_H
#include "CBuildDialog.h"
namespace game_framework {
	class CBuildVillager:public CBuildDialog			 
	{
	public :
		CBuildVillager();
		~CBuildVillager();
		void Build();
	};
}

#endif