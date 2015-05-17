#ifndef CBUILDTOWNCENTER_H
#define CBUILDTOWNCENTER_H
#include "CBuildDialog.h"
namespace game_framework {
	class CBuildTownCenter:public CBuildDialog			 
	{
	public :
		CBuildTownCenter();
		~CBuildTownCenter();
		void Build();
	};
}

#endif