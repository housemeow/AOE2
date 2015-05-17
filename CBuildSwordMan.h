#ifndef CBUILDSWORDMAN_H
#define CBUILDSWORDMAN_H
#include "CBuildDialog.h"
namespace game_framework {

	class CBuildSwordMan:public CBuildDialog			 
	{
		public :
			CBuildSwordMan();
			~CBuildSwordMan();
			void Build();
	};


}

#endif