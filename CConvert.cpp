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
	主要實做:
	螢幕座標轉成地圖座標(Base轉換)
	地圖座標轉成格子座標(地圖軸64單位代表一格)
	格子座標轉成地圖座標(一格有地圖軸64單位)
	地圖座標轉成螢幕座標(Base轉換)
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
		假設地圖為30*20
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
		假設地圖為3*2
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

	CPoint CConvert::GetGridPointByScreenPoint(CPoint sp){//輸入螢幕點得到格子座標**********
		CPoint mapPoint(GetMapPointByScreenPoint(sp));//螢幕轉成地圖座標
		CPoint gridPoint(GetGridPointByMapPoint(mapPoint));//地圖座標轉成格子座標
		return gridPoint;
	}
	CPoint CConvert::GetGridPointByMapPoint(CPoint mp){//輸入地圖座標得到格子座標
		CPoint gridPoint;
		gridPoint.x = (mp.x+6400)/64-100;//+640解決負數的問題
		gridPoint.y = (mp.y+6400)/64-100;//
		return gridPoint;
	}
	CPoint CConvert::GetMapPointByScreenPoint(CPoint sp){//輸入螢幕座標得到地圖座標
		CPoint mapPoint;
		sp+= CGameMap::GetMap()->GetScreenPoint();
		mapPoint.x = sp.y*2+sp.x;
		mapPoint.y = sp.y*2-sp.x;
		return mapPoint;
	}
	CPoint CConvert::GetMapPointByGridPoint(CPoint gp){//輸入格子座標得到地圖座標
		CPoint mapPoint;//得到格子最上面的地圖點
		mapPoint.x = gp.x*64;
		mapPoint.y = gp.y*64;
		return mapPoint;
	}
	CPoint CConvert::GetScreenPointByGridPoint(CPoint gp){//輸入格子座標得到螢幕座標
		CPoint mapPoint(GetMapPointByGridPoint(gp));//格子座標轉成地圖座標
		CPoint screenPoint(GetScreenPointByMapPoint(mapPoint));//地圖座標轉成螢幕座標
		return screenPoint;
	}
	CPoint CConvert::GetScreenPointByMapPoint(CPoint mp){//輸入地圖座標得到螢幕座標
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