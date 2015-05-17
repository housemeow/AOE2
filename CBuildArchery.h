#ifndef CBUILDARCHERY_H
#define CBUILDARCHERY_H
#include "CBuildDialog.h"
namespace game_framework {
	class CBuildArchery:public CBuildDialog
	{
	public :
		CBuildArchery();
		~CBuildArchery();
		void Build();
	};
}

#endif