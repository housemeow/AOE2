#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CAnimationAdvance.h"
namespace game_framework 
{
	CAnimationAdvance::CAnimationAdvance(){
		animation=NULL;
	}

	CMovingBitmap* CAnimationAdvance::GetBitmap(){
		return &(*bmp_iter);
	}

	void CAnimationAdvance::SetAnimation(CAnimation *animation){
		this->animation=animation;
		animation->Reset();
		bmp_iter=animation->GetCurrentBitmapIter();
		delay_counter = animation->DelayCount();
	}

	void CAnimationAdvance::OnMove(){
		if (--delay_counter <= 0)  {
			delay_counter = animation->DelayCount();
			bmp_iter++;
			animation->SetCurrentBitmapIter(bmp_iter);
			if(animation->IsFinalBitmap()){
				animation->Reset();
				bmp_iter=animation->GetCurrentBitmapIter();
			}
		}
	}

	void CAnimationAdvance::SetTopLeft(int x,int y){
		animation->SetTopLeft(x,y);
	}

	void CAnimationAdvance::OnShow()
	{
		animation->SetCurrentBitmapIter(bmp_iter);
		animation->OnShow();
	}
}