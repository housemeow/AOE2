#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMultiGameDialog.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CMultiGameDialog，使用DecorationPattern來讓多Dialog的類別可自動呼叫其滑鼠事件
/////////////////////////////////////////////////////////////////////////////

	CMultiGameDialog::CMultiGameDialog(){
		subGameDialog.clear();
	}
	CMultiGameDialog::~CMultiGameDialog(){}

	void CMultiGameDialog::OnShow(){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			(*it)->OnShow();
		}
	}
	
	void CMultiGameDialog::OnMove(){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			(*it)->OnMove();
		}
	}


	void CMultiGameDialog::OnLeftDown(CMouseState& state){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			if((*it)->PtInRect(state.LeftDownPoint())){
				(*it)->OnLeftDown(state);
			}
		}
	}
	void CMultiGameDialog::OnLeftUp(CMouseState& state){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			if((*it)->PtInRect(state.LeftDownPoint())){
				(*it)->OnLeftUp(state);
			}
		}
	}
	void CMultiGameDialog::OnRightDown(CMouseState& state){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			if((*it)->PtInRect(state.RightDownPoint())){
				(*it)->OnRightDown(state);
			}
		}
	}
	void CMultiGameDialog::OnRightUp(CMouseState& state){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			if((*it)->PtInRect(state.RightDownPoint())){
				(*it)->OnRightUp(state);
			}
		}
	}
	void CMultiGameDialog::OnMouseMove(CMouseState& state){
		vector<CGameDialog*>::iterator it;
		for(it=subGameDialog.begin();it!=subGameDialog.end();it++){
			if((*it)->PtInRect(state.NowPoint())){
				(*it)->OnMouseMove(state);
			}
		}
	}
	void CMultiGameDialog::AddGameDialog(CGameDialog* gameDialog){
		subGameDialog.push_back(gameDialog);
	}
	void CMultiGameDialog::ClearGameDialog(){
		subGameDialog.clear();
	}
}