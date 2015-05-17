#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CResourceTable.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為所有地圖中單位與建築物的基底類別
/////////////////////////////////////////////////////////////////////////////
	CResourceTable::CResourceTable(){
		food=wood=stone=gold=0;
	}
	CResourceTable::CResourceTable(int wood,int food,int gold,int stone){
		this->wood = wood>0 ? wood:0;
		this->food = food>0 ? food:0;
		this->gold = gold>0 ? gold:0;
		this->stone = stone>0 ? stone:0;
	}
	CResourceTable CResourceTable::operator +(const CResourceTable& resource){
		CResourceTable table(wood+resource.Wood(),food+resource.Food(),gold+resource.Gold(),stone+resource.Stone());
		return table;
	}
	CResourceTable CResourceTable::operator -(const CResourceTable& resource){
		CResourceTable table(wood-resource.Wood(),food-resource.Food(),gold-resource.Gold(),stone-resource.Stone());
		return table;
	}
	void CResourceTable::operator +=(const CResourceTable& resource){
		(*this) = (*this)+resource;
	}
	void CResourceTable::operator -=(const CResourceTable& resource){
		(*this) = (*this)-resource;
	}
	bool CResourceTable::operator >=(const CResourceTable& resource){
		return (wood>=resource.wood && food>=resource.food && gold>=resource.gold && stone>=resource.stone);
	}

	void CResourceTable::Reset(){
		food=wood=gold=stone=0;
	}

	int CResourceTable::Wood()const {return wood;}
	int CResourceTable::Food()const {return food;}
	int CResourceTable::Gold()const {return gold;}
	int CResourceTable::Stone()const {return stone;}
}