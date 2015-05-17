#ifndef CBUILDDIALOG_H
#define CBUILDDIALOG_H
#include <vector>
#include "CDialog.h"
#include "CSprite.h"
namespace game_framework {
	class CBuildDialog:public CDialog			 
	{
		public :
			void SetSprite(CSprite* sprite);
			void command();
			virtual void Build(){}
			void OnShow();
		private:
	protected:
			CMovingBitmap *icon;
			CSprite* sprite;
			CResourceTable resourceTable;
	};
}

#endif