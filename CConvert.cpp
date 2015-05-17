#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#ifndef GAMELIB_H
#define GAMELIB_H
#include "gamelib.h"
#endif
#include "CMapTile.h"
#include "CGameMap.h"
#include "CConvert.h"
#include "mygame.h"

namespace game_framework {
	////
	////CConvert
	////
	/*
	�D�n�갵:
	�ù��y���ন�a�Ϯy��(Base�ഫ)
	�a�Ϯy���ন��l�y��(�a�϶b64���N��@��)
	��l�y���ন�a�Ϯy��(�@�榳�a�϶b64���)
	�a�Ϯy���ন�ù��y��(Base�ഫ)
	*/

	
	bool CConvert::GridRectInRange(const CRect& r){
		if(GridPointInRange(r.TopLeft()) && GridPointInRange(r.BottomRight())){
			return true;
		}else{
			return false;
		}
	}

	bool CConvert::MapPointInRange(const CPoint& p){
		CGameMap *map = CGameMap::GetMap();
		if(p.x<0 || p.x>=map->GridSizeX()*64 || p.y<0 || p.y>=map->GridSizeY()*64){
			return false;
		}else{
			return true;
		}
	}
	bool CConvert::GridPointInRange(const CPoint& p){
		CGameMap *map = CGameMap::GetMap();
		if(p.x<0 || p.x>=map->GridSizeX() || p.y<0 || p.y>=map->GridSizeY()){
			return false;
		}else{
			return true;
		}
	}

	void CConvert::FitGridPoint(CPoint& p){
		/*
		���]�a�Ϭ�30*20
		0<=x<=29
		0<=y<=19
		*/
		CGameMap *map = CGameMap::GetMap();
		p.x = (p.x<0) ? 0 : p.x;
		p.x = (p.x>=map->GridSizeX()) ? map->GridSizeX()-1 : p.x;
		p.y = (p.y<0) ? 0 : p.y;
		p.y = (p.y>=map->GridSizeY()) ? map->GridSizeY()-1 : p.y;
	}
	void CConvert::FitMapPoint(CPoint& p){
		/*
		���]�a�Ϭ�3*2
		0<=x<=64*3-1
		0<=x<=191
		0<=y<=64*2-1
		0<=y<=127
		*/
		CGameMap *map = CGameMap::GetMap();
		p.x = (p.x<0) ? 0 : p.x;
		p.x = (p.x>=map->GridSizeX()*64) ? map->GridSizeX()*64-1 : p.x;
		p.y = (p.y<0) ? 0 : p.y;
		p.y = (p.y>=map->GridSizeY()*64) ? map->GridSizeY()*64-1 : p.y;
	}
	void CConvert::FitGridRect(CRect& rect){
		rect.NormalizeRect();
		CGameMap *map = CGameMap::GetMap();
		rect &= map->GridRect();
	}

	CPoint CConvert::GetGridPointByScreenPoint(CPoint sp){//��J�ù��I�o���l�y��**********
		CPoint mapPoint(GetMapPointByScreenPoint(sp));//�ù��ন�a�Ϯy��
		CPoint gridPoint(GetGridPointByMapPoint(mapPoint));//�a�Ϯy���ন��l�y��
		return gridPoint;
	}
	CPoint CConvert::GetGridPointByMapPoint(CPoint mp){//��J�a�Ϯy�бo���l�y��
		CPoint gridPoint;
		gridPoint.x = (mp.x+6400)/64-100;//+640�ѨM�t�ƪ����D
		gridPoint.y = (mp.y+6400)/64-100;//
		return gridPoint;
	}
	CPoint CConvert::GetMapPointByScreenPoint(CPoint sp){//��J�ù��y�бo��a�Ϯy��
		CPoint mapPoint;
		sp+= CGameMap::GetMap()->GetScreenPoint();
		mapPoint.x = sp.y*2+sp.x;
		mapPoint.y = sp.y*2-sp.x;
		return mapPoint;
	}
	CPoint CConvert::GetMapPointByGridPoint(CPoint gp){//��J��l�y�бo��a�Ϯy��
		CPoint mapPoint;//�o���l�̤W�����a���I
		mapPoint.x = gp.x*64;
		mapPoint.y = gp.y*64;
		return mapPoint;
	}
	CPoint CConvert::GetScreenPointByGridPoint(CPoint gp){//��J��l�y�бo��ù��y��
		CPoint mapPoint(GetMapPointByGridPoint(gp));//��l�y���ন�a�Ϯy��
		CPoint screenPoint(GetScreenPointByMapPoint(mapPoint));//�a�Ϯy���ন�ù��y��
		return screenPoint;
	}
	CPoint CConvert::GetScreenPointByMapPoint(CPoint mp){//��J�a�Ϯy�бo��ù��y��
		CPoint screenPoint;
		screenPoint.x = (mp.x-mp.y)/2;
		screenPoint.y = (mp.x+mp.y)/4;
		screenPoint -= CGameMap::GetMap()->GetScreenPoint();
		return screenPoint;
	}
	CPoint CConvert::GetWorldPointByGridPoint(CPoint gp){
		CPoint mapPoint(GetMapPointByGridPoint(gp));
		CPoint worldPoint(GetWorldPointByMapPoint(mapPoint));
		return worldPoint;
	}
	CPoint CConvert::GetWorldPointByMapPoint(CPoint mp){
		CPoint worldPoint;
		worldPoint.x = (mp.x-mp.y)/2;
		worldPoint.y = (mp.x+mp.y)/4; 
		return worldPoint;
	}
}