#ifndef CMULTIGAMEDIALOG_H
#define CMULTIGAMEDIALOG_H

#include <vector>
#include "CGameDialog.h"

namespace game_framework {

	class CMultiGameDialog:public CGameDialog
	{
	public:
		CMultiGameDialog();
		~CMultiGameDialog();
		virtual void OnShow();
		virtual void OnMove();
		virtual void OnLeftDown(CMouseState& state);
		virtual void OnLeftUp(CMouseState& state);
		virtual void OnRightDown(CMouseState& state);
		virtual void OnRightUp(CMouseState& state);
		virtual void OnMouseMove(CMouseState& state);
		void AddGameDialog(CGameDialog* gameDialog);
		void ClearGameDialog();
	private:
		 vector<CGameDialog*> subGameDialog; 
	};
}
#endif