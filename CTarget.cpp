#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CTarget.h"
#include "CSprite.h"
#include "CConvert.h"
#include "mygame.h"


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為Sprite鎖定的目標，可能是一個點或是一個物件
/////////////////////////////////////////////////////////////////////////////
	CTarget::CTarget():isNull(true),isPoint(false),isSprite(false){
		this->sprite = NULL;
	}
	CTarget::CTarget(CPoint point):isNull(false),isPoint(true),isSprite(false){
		this->mapPoint = point;
		this->sprite = NULL;
	}
	CTarget::CTarget(CSprite* sprite):isNull(false),isPoint(false),isSprite(true){
		this->sprite = sprite;
	}

	CSprite* CTarget::Sprite(){return sprite;}
	CPoint CTarget::MapPoint(){return mapPoint;}
	bool CTarget::IsPoint(){return isPoint;}
	bool CTarget::IsNull(){return isNull;}
	bool CTarget::IsSprite(){return isSprite;}
	CTarget CTarget::Null(){return CTarget();}
	bool CTarget::IsAttackable(CSprite* sprite){
		if(IsSprite()){
			return Sprite()->IsAttackable() && sprite->Player() !=Sprite()->Player();
		}
		return false;
	}
	bool CTarget::IsCollectable(CSprite* sprite){
		if(IsSprite()){
			return Sprite()->IsCollectable() && InRange(sprite,1);
		}
		return false;
	}
	bool CTarget::IsRepairable(CSprite* sprite){
		if(IsSprite()){
			return Sprite()->IsRepairable() && InRange(sprite,1) && sprite->Player()==Sprite()->Player();
		}
		return false;
	}
	bool CTarget::InRange(CSprite* sprite,int range){
		CRect rect(this->sprite->GridRect());
		rect.InflateRect(range,range,range+1,range+1);
		if(rect.PtInRect(sprite->GridPoint())){
			return true;
		}
		return false;
	}
}