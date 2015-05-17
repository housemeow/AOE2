#ifndef CBUILDARCHER_H
#define CBUILDARCHER_H
#include "CBuildDialog.h"
namespace game_framework {

	class CBuildArcher:public CBuildDialog			 
	{
	public :
		CBuildArcher();
		~CBuildArcher();
		void Build();
	};
}

#endif