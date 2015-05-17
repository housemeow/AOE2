#ifndef COBJECT_H
#define COBJECT_H

#include "CPlayer.h"

namespace game_framework {
	class CGameObject;//先行宣告讓CTarget可以用
/////////////////////////////////////////////////////////////////////////////
// 這個class為Object鎖定的目標，可能是一個點或是一個物件
/////////////////////////////////////////////////////////////////////////////
	class CTarget{
	public:
		CTarget(CGameObject*);
		CTarget(CPoint);
		(CGameObject*)& Object();
		CPoint& Point();
		bool& IsPoint();
	private:
		bool isPoint;
		CGameObject* object;
		CPoint point;
	};


/////////////////////////////////////////////////////////////////////////////
// 這個class為所有地圖中單位與建築物的基底類別
/////////////////////////////////////////////////////////////////////////////
	class CGameObject{
	public:
		CGameObject();
		virtual ~CGameObject();
		virtual void OnMove(){}
		virtual void OnAction(){}
		virtual void SetTarget(CGameObject* obj){}
		virtual void FindTarget(){}
		virtual void Attack(){}
		virtual void Collect(){}
		virtual void Repair(){}

		void OnSelected();
		void OnUnselected();

		virtual void OnTargetted(CGameObject* obj){}
		virtual void OnAttacked(CGameObject* obj, int damage){}
		virtual void OnCollected(CGameObject* obj){}
		virtual void OnRepaired(CGameObject* obj){}
	
		virtual void OnShow(){}

		bool IsAttackable();
		bool IsCollectable();
		bool IsRepairable();
		int HP();
		int MaxHP();
		int Atk();
		int Def();
		CRect ScreenRect();
		CPoint GridPoint(){};
		CPoint MapPoint(){};
	protected:
		//資料
		string nane;		//類別名稱
		string type;		//種類
		int maxHp;			//最大生命值
		int hp;				//目前生命值，對應到資源時代表資源數量
		CPoint mapPoint;	//目前所在的地圖點
		CPlayer *player;	//所屬的玩家
		//控制
		bool isAttackable;	//是否可被攻擊的屬性
		bool isCollectable;	//是否可被採集的屬性
		bool isRepairable;	//是否可被修復的屬性
		bool isSelected;
		CTarget* target;	//鎖定的目標
		//顯示
		CMovingBitmap icon;	//顯示在SelectionPanel的小圖示
		CMovingBitmap *bmp;	//目前顯示的點陣圖






		//特殊屬性
		int atkSpeed;		//攻擊速度
		int atkRange;		//攻擊距離
		int atkUnit;		//對一般單位的攻擊力
		int atkVillager;	//對村民的攻擊力
		int atkSwordman;	//對劍士的攻擊力
		int atkSpearman;	//對矛兵的攻擊力
		int atkBowman;		//對弓箭手的攻擊力
		int atkKnight;		//對騎兵的的攻擊力
		int atkBuilding;	//對一般建築的的攻擊力
		int atkRockBuilding;//對石造建築的的攻擊力
		int atkWoodBuilding;//對木造建築的的攻擊力
		int direct;			//目前的面向
		int moveSpeed;		//移動速度
		int def;			//防禦力
	private:
		static int count;
		const int id;
	};
}
#endif