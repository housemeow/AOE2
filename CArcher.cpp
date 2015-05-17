#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CResourceCenter.h"
#include "CUnit.h"
#include "CDialog.h"
#include "CArcher.h"
#include "mygame.h"

namespace game_framework {
	
	CArcher::CArcher(){
		bmp=CBitmapCollection::GetBitmapCollection()->GetBitmap(SPRITES_UNITS_ARCHER);
		icon=CBitmapCollection::GetBitmapCollection()->GetBitmap(ICON_UNITS_ARCHER);
		//bmp = new CMovingBitmap();
		//bmp->LoadBitmapA("Bitmaps/Sprites/Units/Archer/archer.bmp",0);
		
		//icon=new CMovingBitmap(ICON_UNITS_ARCHER);
		//icon->LoadBitmapA("Bitmaps/Icons/Units/archer.bmp",-1);
		iconDialog.pic=*icon;
		moveSpeed=9;
		atkSpeed = 17;
		atkUnit = 4;
		atkGridRange= 6;
		targetRange = 5;
		hp = 20;
		this->maxHp = 20;
		isAttackable = true;
		isCollectable=false;
		isRepairable=false;
		arrow.LoadBitmap("Bitmaps/Sprites/Units/Archer/M_ARRO_F.SLP 0073.bmp",0);
	}
	CArcher::~CArcher(){
		bmp=NULL;
		icon=NULL;
	}
	void CArcher::OnMove(){
		CUnit::OnMove();
		//if(this->target.IsSprite()){
		//	CPoint point(arrow.Left(),arrow.Top());
		//	CPoint v(target.Sprite()->MapPoint()-this->mapPoint);
		//	arrow.SetTopLeft(arrow.left,arrow.top);
		//	
		//}
	}
	void CArcher::SetArrowTopLeft(CPoint point){
		//arrowMapPoint = point;
		//arrow.SetTopLeft(point.x,point.y);
	}
	void CArcher::OnShow(){
		CSprite::OnShow();
		//arrow.ShowBitmap();
	}
	
}