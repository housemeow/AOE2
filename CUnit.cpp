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
		if(GridPoint()!=newGridPoint){//移動到新的地方
			if(map->GetMapTile(newGridPoint)->Sprites().empty()){//可以移動
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
		{//如果已達攻擊範圍、採集範圍、修復範圍則停止移動
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
		if(target.Path.empty()){//計算路徑
			int flag[100][100]={};
			queue<CPoint> path;
			path.push(this->GridPoint());
			while(!path.empty()){//產生路徑
				CPoint nowPoint = path.front();
				if(nowPoint == CConvert::GetGridPointByMapPoint(targetMapPoint)){//如果已經到達路徑就直接跳出
					break;
				}else{//如果還沒到終點就把點給pop出來*(保留終點的queue)
					path.pop();
				}
				CPoint nextPoint;
				//上y-1
				nextPoint = nowPoint + CPoint(0,-1);
				if(map->GridRect().PtInRect(nextPoint)){
					//如果目前這個點再地圖內而且沒障礙物
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//如果這個點沒走過
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//下y+1
				nextPoint = nowPoint + CPoint(0,1);
				if(map->GridRect().PtInRect(nextPoint)){
					//如果目前這個點再地圖內而且沒障礙物
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//如果這個點沒走過
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//左x-1
				nextPoint = nowPoint + CPoint(-1,0);
				if(map->GridRect().PtInRect(nextPoint)){
					//如果目前這個點再地圖內而且沒障礙物
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//如果這個點沒走過
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
				//右x+1
				nextPoint = nowPoint + CPoint(1,0);
				if(map->GridRect().PtInRect(nextPoint)){
					//如果目前這個點再地圖內而且沒障礙物
					if(map->GetMapTile(nextPoint)->Sprites().size()==0){
						if(flag[nextPoint.y][nextPoint.x]==0){
							//如果這個點沒走過
							flag[nextPoint.y][nextPoint.x] = flag[nowPoint.y][nowPoint.x]+1;
							path.push(nextPoint);
						}
					}
				}
			}
			CPoint nowPoint = CConvert::GetGridPointByMapPoint(targetMapPoint);//從終點找回來
			stack<CPoint> reverseQueue;
			reverseQueue.push(nowPoint);
			flag[this->GridPoint().y][this->GridPoint().x]=0;//把起點改成0，而終止條件就是走到起點
			while(flag[nowPoint.y][nowPoint.x]!=0){
				CPoint tempPoint;
				//上
				tempPoint = nowPoint + CPoint(0,-1);
				if(map->GridRect().PtInRect(tempPoint)){//再地圖範圍內
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//找到一個接近起點的點
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//右
				tempPoint = nowPoint + CPoint(1,0);
				if(map->GridRect().PtInRect(tempPoint)){//再地圖範圍內
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//找到一個接近起點的點
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//左
				tempPoint = nowPoint + CPoint(-1,0);
				if(map->GridRect().PtInRect(tempPoint)){//再地圖範圍內
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//找到一個接近起點的點
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
				//下
				tempPoint = nowPoint + CPoint(0,1);
				if(map->GridRect().PtInRect(tempPoint)){//再地圖範圍內
					if((flag[tempPoint.y][tempPoint.x]+1) == flag[nowPoint.y][nowPoint.x]){//找到一個接近起點的點
						nowPoint = tempPoint;
						reverseQueue.push(tempPoint);
						continue;
					}
				}
			}
			while(!reverseQueue.empty()){//將queue倒轉
				target.Path.push(reverseQueue.top());
				reverseQueue.pop();
			}
		}
		targetMapPoint = target.Path.front();//下一個目標格
		CPoint originPoint = this->mapPoint;
		for(int i=0;i<moveSpeed;i++){
			if(CConvert::GetGridPointByMapPoint(mapPoint).x<targetMapPoint.x){//原本的x太小 所以x++
				Move(mapPoint+CPoint(1,0));
			}else if(CConvert::GetGridPointByMapPoint(mapPoint).x>targetMapPoint.x){//原本的x太大 所以x--
				Move(mapPoint-CPoint(1,0));
			}
			if(CConvert::GetGridPointByMapPoint(mapPoint).y<targetMapPoint.y){//原本的y太小 所以y++
				Move(mapPoint+CPoint(0,1));
			}else if(CConvert::GetGridPointByMapPoint(mapPoint).y>targetMapPoint.y){//原本的y太大 所以y--
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
		//畫圓圈
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC

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
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}