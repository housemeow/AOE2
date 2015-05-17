#ifndef CBUILDKNIGHT_H
#define CBUILDKNIGHT_H
#include "CBuildDialog.h"
namespace game_framework {

	class CBuildKnight:public CBuildDialog			 
	{
	public :
		CBuildKnight();
		~CBuildKnight();
		void Build();
	};


}

#endif