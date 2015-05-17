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
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
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
		set<CSprite*> targetedSprites;	//��w�ۤv��Sprites

		bool IsBuilding();
		bool IsUnit();
		bool IsResource();
		int targetRange;				//�Ĩ��u�ê��A�ɪ���w�d��
		CResourceTable spendResource;
	private:
		static int count;				//���󲣥ͪ��p��
		const int id;					//���󪺽s��
	protected:
		CTarget target;					//��w���ؼ�
		CPoint mapPoint;				//�ثe���y���I(2.5D�y��)
		CSize gridSize;					//Sprite�ү��o��l�j�p
		bool isBuilding;
		bool isUnit;
		bool isResource;
		bool isAttackable;				//�i�_�Q����
		bool isCollectable;				//�i�_�Q�Ķ�
		bool isRepairable;				//�i�_�Q�״_
		bool isSelected;				//�O�_�QSelectionPanel���
		int maxHp;						//�̤j��q(�p�G�OResource�N���l�귽)
		int hp;							//�ثe��q(�p�G�OResource�N��Ѿl�귽)
		CPlayer *player;				//���ݪ��a
		CIconDialog iconDialog;

		int atkGridRange;				//�����Z��
		int atkSpeed;					//�����t��
		int atkCount;
		int atkUnit;					//�����@���쪺�����O
		int atkSwordman;				//�����C�h�������O
		int atkArcher;					//�����}�b�⪺�����O
		int atkSpearman;				//�����٧L�������O
		int atkKnight;					//�����M�h�������O
		int def;						//���m�O
		//�p�G�ݭn�i������P���m��աA��Y�س�즳�S���m�O
		
		int direct;						//�ثe����
		int moveSpeed;					//���ʳt��
		int viewDistance;				//�����Z��
	
		int collectSpeed;				//�Ķ��t��
		int collectCount;				//�Ķ��p�ƾ�
		int repairCount;

		CMovingBitmap* bmp;		//�ثe��ܦAGameMap���Ϥ��A�ǥ�Animator�����
		CMovingBitmap* icon;
		
		CAnimationAdvance animation;
		CResourceTable resourceTable;	//�Ķ��귽�q
	};
}
#endif