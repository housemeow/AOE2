#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include <stack>
#include "CSprite.h"
#include "CUnit.h"
#include "CConvert.h"
#include <cmath>
#include "mygame.h"

namespace game_framework {

	CUnit::CUnit(){
		idleCount = 0;
		viewDistance = 5;
		isUnit = true;
	}
	CUnit::~CUnit(){}


	void CUnit::Move(const CPoint& newMapPoint){
		CPoint newGridPoint(CConvert::GetGridPointByMapPoint(newMapPoint));
		CGameMap* map = CGameMap::GetMap();
		this->ClearVisionCount();
		if(GridPoint()!=newGridPoint){//���ʨ�s���a��
			if(map->GetMapTile(newGridPoint)->Sprites().empty()){//�i�H����
				this->SetMapPointAndMapTile(newMapPoint);
			}
		}else{
			this->SetMapPoint(newMapPoint);
		}
		this->SetVisionCount();
	}
	void CUnit::OnMove(){
		if(target.IsNull()){
			return;
		}
		if((target.IsAttackable(this) && target.InRange(this,this->atkGridRange)) || target.IsCollectable(this) || target.IsRepairable(this))
		{//�p�G�w�F�����d��B�Ķ��d��B�״_�d��h�����
			return;
		}
		CPoint targetMapPoint;
		if(target.IsPoint()){
			if(target.MapPoint()==this->MapPoint()){
				target = CTarget::Null();
				return;
			}else{
				targetMapPoint = target.MapPoint();
			}
		}else{
			targetMapPoint = target.Sprite()->MapPoint();
		}
		
		
		CGameMap* map = CGameMap::GetMap();
		if(target.Path.empty()){//�p����|
			int flag[100][100]={};
			queue<CPoint> path;
			path.push(this->GridPoint());
			while(!path.empty()){//���͸��|
				CPoint nowPoint = path.front();
				if(nowPoint == CConvert::GetGridPointByMapPoint(targetMapPoint)){//�p�G�w�g��F���|�N�������X
					break;
				}else{//�p�G�٨S����I�N���I��pop�X��*(�O�d���I��queue)
					path.pop();
				}
				CPoint nextPoint;
				//�Wy-1
				nextPoint = nowPoint + CPoint(0,-1);
				if(map->GridRect().PtInRect(nextPoint)){
					//�p�G�ثe�o���I�A�a�Ϥ��ӥB�S��ê��
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//�p�G�o���I�S���L
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//�Uy+1
				nextPoint = nowPoint + CPoint(0,1);
				if(map->GridRect().PtInRect(nextPoint)){
					//�p�G�ثe�o���I�A�a�Ϥ��ӥB�S��ê��
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//�p�G�o���I�S���L
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//��x-1
				nextPoint = nowPoint + CPoint(-1,0);
				if(map->GridRect().PtInRect(nextPoint)){
					//�p�G�ثe�o���I�A�a�Ϥ��ӥB�S��ê��
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//�p�G�o���I�S���L
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//�kx+1
				nextPoint = nowPoint + CPoint(1,0);
				if(map->GridRect().PtInRect(nextPoint)){
					//�p�G�ثe�o���I�A�a�Ϥ��ӥB�S��ê��
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//�p�G�o���I�S���L
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
			}
			CPoint nowPoint = CConvert::GetGridPointByMapPoint(targetMapPoint);//�q���I��^��
			stack<CPoint> reverseQueue;
			reverseQueue.push(nowPoint);
			flag[this->GridPoint().y][this->GridPoint().x]=0;//��_�I�令0�A�Ӳפ����N�O����_�I
			while(flag[nowPoint.y][nowPoint.x]!=0){
				CPoint tempPoint;
				//�W
				tempPoint = nowPoint + CPoint(0,-1);
				if(map->GridRect().PtInRect(tempPoint)){//�A�a�Ͻd��
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//���@�ӱ���_�I���I
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//�k
				tempPoint = nowPoint + CPoint(1,0);
				if(map->GridRect().PtInRect(tempPoint)){//�A�a�Ͻd��
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//���@�ӱ���_�I���I
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//��
				tempPoint = nowPoint + CPoint(-1,0);
				if(map->GridRect().PtInRect(tempPoint)){//�A�a�Ͻd��
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//���@�ӱ���_�I���I
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//�U
				tempPoint = nowPoint + CPoint(0,1);
				if(map->GridRect().PtInRect(tempPoint)){//�A�a�Ͻd��
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//���@�ӱ���_�I���I
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
			}
			while(!reverseQueue.empty()){//�Nqueue����
				target.Path.push(reverseQueue.top());
				reverseQueue.pop();
			}
		}
		targetMapPoint = target.Path.front();//�U�@�ӥؼЮ�
		CPoint originPoint = this->mapPoint;
		for(int i=0;i<moveSpeed;i++){
			if(CConvert::GetGridPointByMapPoint(mapPoint).x<targetMapPoint.x){//�쥻��x�Ӥp �ҥHx++
				Move(mapPoint+CPoint(1,0));
			}else if(CConvert::GetGridPointByMapPoint(mapPoint).x>targetMapPoint.x){//�쥻��x�Ӥj �ҥHx--
				Move(mapPoint-CPoint(1,0));
			}
			if(CConvert::GetGridPointByMapPoint(mapPoint).y<targetMapPoint.y){//�쥻��y�Ӥp �ҥHy++
				Move(mapPoint+CPoint(0,1));
			}else if(CConvert::GetGridPointByMapPoint(mapPoint).y>targetMapPoint.y){//�쥻��y�Ӥj �ҥHy--
				Move(mapPoint-CPoint(0,1));
			}
			if(CConvert::GetGridPointByMapPoint(mapPoint)==targetMapPoint){
				target.Path.pop();
				if(target.Path.empty()){
					return;
				}
				targetMapPoint = target.Path.front();
			}
		}
	}

	void CUnit::Attack(){
		atkCount++;
		if(atkCount>=atkSpeed){
			atkCount=0;
			int damage = this->atkUnit - target.Sprite()->Def();
			if(damage<1)damage=1;
			target.Sprite()->OnAttacked(this,damage);
		}
	}

	void CUnit::OnShowSelectedLine(){
		//�e���
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC

		CPen penBlack;
		CPen penWhite;
		CPen* pOldPen;
		penBlack.CreatePen(PS_SOLID,1,RGB(0,0,0));
		penWhite.CreatePen(PS_SOLID,1,RGB(255,255,255));
		pOldPen = pDC->SelectObject(&penBlack);
		CRect rect;
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		rect.SetRect(	screenPoint.x-bmp->Width()/2-10,
						screenPoint.y-25,
						screenPoint.x+bmp->Width()/2+10,
						screenPoint.y+5);
		pDC->Arc(rect,rect.TopLeft(),rect.TopLeft());
		rect.MoveToY(rect.top+1);
		pDC->SelectObject(&penWhite);
		pDC->Arc(rect,rect.TopLeft(),rect.TopLeft());
		pDC->SelectObject(pOldPen);						//
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
}