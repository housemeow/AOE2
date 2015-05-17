#ifndef CSPRITE_H
#define CSPRITE_H

#include "CTarget.h"
#include "CPlayer.h"
#include "CMapTile.h"
#include "CDialog.h"

#include "CAnimationAdvance.h"
#include "CResourceTable.h"


namespace game_framework {

	class CAttackTable{
	public:
		CAttackTable();
	private:
		int atk;
	};
	
/////////////////////////////////////////////////////////////////////////////
// 這個class為所有地圖中單位與建築物的基底類別
/////////////////////////////////////////////////////////////////////////////
	class CMapTile;
	class CSprite{
	public:
		CSprite();
		virtual ~CSprite();

		virtual void OnMove(){}
		void OnAction();
		virtual void PlaySelectedSound(){};

		virtual void Attack(){}
		virtual void OnAttacked(CSprite* sprite,int damage);
		virtual void Collect(){}
		virtual void OnCollected(CSprite* sprite){}
		virtual void Repair(){}
		virtual void OnRepaired(CSprite* sprite){}

		void OnDie();

		virtual void OnSelected();
		void OnUnselected();

		void SetTarget(CTarget);
		void OnTargeted(CSprite* sprite);
		
		void OnShow();
		void OnShowSprite();
		virtual void OnShowSelectedLine()=0;

		void FindTarget();
		int FindXAxis(int top,int bottom,int y);
		int FindYAxis(int left,int right,int x);

		virtual void FunctionDialogComposite(){}

		CResourceTable& ResourceTable();

		void SetMapPointAndMapTile(CPoint mapPoint);
		void SetMapPoint(CPoint mapPoint);
		void CancelTarget(CSprite* sprite);
		void SetMapTile();
		void ClearMapTile();
		void SetVisionCount();
		void ClearVisionCount();
		void SetExplored();
		void SetPlayer(CPlayer* player);
		virtual void FitMapPoint(CPoint mapPoint){};

		bool IsAttackable();
		bool IsCollectable();
		bool IsRepairable();
		bool IsSelected();
		int AtkGridRange()const;
		int HP()const;
		int MaxHP()const;
		int Atk()const;
		int Def()const;
		CRect ScreenRect();
		CPoint MapPoint();
		CPoint GridPoint();
		int ID()const;
		CPlayer* Player();
		CTarget& Target();
		CRect GridRect();
		CRect VisionRect();
		
		class CIconDialog: public CDialog
		{
			public :
				void command();
				CSprite* sprite;
		};
		CIconDialog* IconDialog();
		set<CSprite*> targetedSprites;	//鎖定自己的Sprites

		bool IsBuilding();
		bool IsUnit();
		bool IsResource();
		int targetRange;				//採取守衛狀態時的鎖定範圍
		CResourceTable spendResource;
	private:
		static int count;				//物件產生的計數
		const int id;					//物件的編號
	protected:
		CTarget target;					//鎖定的目標
		CPoint mapPoint;				//目前的座標點(2.5D座標)
		CSize gridSize;					//Sprite所站得格子大小
		bool isBuilding;
		bool isUnit;
		bool isResource;
		bool isAttackable;				//可否被攻擊
		bool isCollectable;				//可否被採集
		bool isRepairable;				//可否被修復
		bool isSelected;				//是否被SelectionPanel選取
		int maxHp;						//最大血量(如果是Resource代表原始資源)
		int hp;							//目前血量(如果是Resource代表剩餘資源)
		CPlayer *player;				//所屬玩家
		CIconDialog iconDialog;

		int atkGridRange;				//攻擊距離
		int atkSpeed;					//攻擊速度
		int atkCount;
		int atkUnit;					//攻擊一般單位的攻擊力
		int atkSwordman;				//攻擊劍士的攻擊力
		int atkArcher;					//攻擊弓箭手的攻擊力
		int atkSpearman;				//攻擊矛兵的攻擊力
		int atkKnight;					//攻擊騎士的攻擊力
		int def;						//防禦力
		//如果需要可把攻擊與防禦對調，對某種單位有特殊防禦力
		
		int direct;						//目前面相
		int moveSpeed;					//移動速度
		int viewDistance;				//視野距離
	
		int collectSpeed;				//採集速度
		int collectCount;				//採集計數器
		int repairCount;

		CMovingBitmap* bmp;		//目前顯示再GameMap的圖片，藉由Animator來顯示
		CMovingBitmap* icon;
		
		CAnimationAdvance animation;
		CResourceTable resourceTable;	//採集資源量
	};
}
#endif