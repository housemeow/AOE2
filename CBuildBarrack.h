#ifndef CBUILDBARRACK_H
#define CBUILDBARRACK_H
#include "CBuildDialog.h"
namespace game_framework {
	class CBuildBarrack:public CBuildDialog			 
	{
	public :
		CBuildBarrack();
		~CBuildBarrack();
		void Build();
	};
}

#endif