#ifndef COBJECT_H
#define COBJECT_H

#include "CPlayer.h"

namespace game_framework {
	class CGameObject;//����ŧi��CTarget�i�H��
/////////////////////////////////////////////////////////////////////////////
// �o��class��Object��w���ؼСA�i��O�@���I�άO�@�Ӫ���
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
// �o��class���Ҧ��a�Ϥ����P�ؿv���������O
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
		//���
		string nane;		//���O�W��
		string type;		//����
		int maxHp;			//�̤j�ͩR��
		int hp;				//�ثe�ͩR�ȡA������귽�ɥN��귽�ƶq
		CPoint mapPoint;	//�ثe�Ҧb���a���I
		CPlayer *player;	//���ݪ����a
		//����
		bool isAttackable;	//�O�_�i�Q�������ݩ�
		bool isCollectable;	//�O�_�i�Q�Ķ����ݩ�
		bool isRepairable;	//�O�_�i�Q�״_���ݩ�
		bool isSelected;
		CTarget* target;	//��w���ؼ�
		//���
		CMovingBitmap icon;	//��ܦbSelectionPanel���p�ϥ�
		CMovingBitmap *bmp;	//�ثe��ܪ��I�}��






		//�S���ݩ�
		int atkSpeed;		//�����t��
		int atkRange;		//�����Z��
		int atkUnit;		//��@���쪺�����O
		int atkVillager;	//������������O
		int atkSwordman;	//��C�h�������O
		int atkSpearman;	//��٧L�������O
		int atkBowman;		//��}�b�⪺�����O
		int atkKnight;		//���M�L���������O
		int atkBuilding;	//��@��ؿv���������O
		int atkRockBuilding;//��۳y�ؿv���������O
		int atkWoodBuilding;//���y�ؿv���������O
		int direct;			//�ثe�����V
		int moveSpeed;		//���ʳt��
		int def;			//���m�O
	private:
		static int count;
		const int id;
	};
}
#endif