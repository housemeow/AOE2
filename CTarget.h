#ifndef CTARGET_H
#define CTARGET_H

#include <queue>

namespace game_framework {
class CSprite;
/////////////////////////////////////////////////////////////////////////////
// 這個class為Sprite鎖定的目標，可能是一個點或是一個物件
/////////////////////////////////////////////////////////////////////////////
class CTarget{
	public:
		CTarget();									//Null的目標
		CTarget(CSprite*);							//指定Sprite的目標
		CTarget(CPoint);							//地圖點的目標

		CSprite* Sprite();							//回傳Sprite物件
		CPoint MapPoint();							//回傳地圖點
		bool IsPoint();								//此目標是否為地圖點
		bool IsNull();								//此目標是否為空
		bool IsSprite();							//此目標是否為Sprite物件
		bool IsAttackable(CSprite* sprite);			//此目標是否可被攻擊
		bool IsCollectable(CSprite* sprite);		//此目標是否可被採集
		bool IsRepairable(CSprite* sprite);			//此目標是否可被修復
		bool InRange(CSprite* sprite,int range);	//此目標是否再範圍內
		static CTarget Null();						//靜態方法，回傳一Null目標，與CTarget()同
		queue<CPoint> Path;
	private:
		bool isPoint;								//
		bool isNull;								//
		bool isSprite;								//
		CSprite* sprite;							//
		CPoint mapPoint;							//
	};
}
#endif