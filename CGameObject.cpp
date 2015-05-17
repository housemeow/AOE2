#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CGameObject.h"
#include "CPlayer.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class��Object��w���ؼСA�i��O�@���I�άO�@�Ӫ���
/////////////////////////////////////////////////////////////////////////////
	CTarget::CTarget(CGameObject* object){
		this->object = object;
		this->isPoint=false;
	}
	CTarget::CTarget(CPoint point){
		this->point = point;
		this->isPoint = true;
	}
	CGameObject*& CTarget::Object(){return object;}
	CPoint& CTarget::Point(){return point;}
	bool& CTarget::IsPoint(){return isPoint;}


/////////////////////////////////////////////////////////////////////////////
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
/////////////////////////////////////////////////////////////////////////////

	int CGameObject::count=0;


	CGameObject::CGameObject():id(CGameObject::count++){
		target=NULL;
		mapPoint = CPoint(0,0);
		this->isAttackable=false;
		this->isCollectable=false;
		this->isRepairable=false;
		isSelected=false;
		hp = 0;
		maxHp=0;
	}
	CGameObject::~CGameObject(){
		if(target!=NULL){
			delete target;
			target=NULL;
		}
	}
	
	
	void CGameObject::OnSelected(){isSelected=true;}
	void CGameObject::OnUnselected(){isSelected=false;}


	
	bool CGameObject::IsAttackable(){return isAttackable;}
	bool CGameObject::IsCollectable(){return isCollectable;}
	bool CGameObject::IsRepairable(){return isRepairable;}
	
	int CGameObject::HP(){return hp;}
	int CGameObject::MaxHP(){return maxHp;}
	int CGameObject::Atk(){return atkUnit;}
	int CGameObject::Def(){return def;}
	CRect CGameObject::ScreenRect(){return CRect(mapPoint,CSize(bmp->Width(),bmp->Height()));}

}