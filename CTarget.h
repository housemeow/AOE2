#ifndef CTARGET_H
#define CTARGET_H

#include <queue>

namespace game_framework {
class CSprite;
/////////////////////////////////////////////////////////////////////////////
// �o��class��Sprite��w���ؼСA�i��O�@���I�άO�@�Ӫ���
/////////////////////////////////////////////////////////////////////////////
class CTarget{
	public:
		CTarget();									//Null���ؼ�
		CTarget(CSprite*);							//���wSprite���ؼ�
		CTarget(CPoint);							//�a���I���ؼ�

		CSprite* Sprite();							//�^��Sprite����
		CPoint MapPoint();							//�^�Ǧa���I
		bool IsPoint();								//���ؼЬO�_���a���I
		bool IsNull();								//���ؼЬO�_����
		bool IsSprite();							//���ؼЬO�_��Sprite����
		bool IsAttackable(CSprite* sprite);			//���ؼЬO�_�i�Q����
		bool IsCollectable(CSprite* sprite);		//���ؼЬO�_�i�Q�Ķ�
		bool IsRepairable(CSprite* sprite);			//���ؼЬO�_�i�Q�״_
		bool InRange(CSprite* sprite,int range);	//���ؼЬO�_�A�d��
		static CTarget Null();						//�R�A��k�A�^�Ǥ@Null�ؼСA�PCTarget()�P
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