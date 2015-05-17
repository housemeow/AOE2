#ifndef CGAMEMAP_H
#define CGAMEMAP_H

#include "CMapTile.h"

#define MAX_SIDE 200

namespace game_framework {
	////
	////CGameMap
	////

	class CGameMap{
	public :
		static void InitMap(int side);		//初始化Map物件，最多MAX_SIDE*MAX_SIDE的地圖
		static CGameMap* GetMap();				//取得GameMap的實體，如果沒有就創造一個新的
		static void ReleaseMap();				//釋放目前的GameMap

		void OnMove();							//移動地圖，這邊會做螢幕座標校準
		void SetMovingLeft(bool flag);			//設定螢幕往左移動
		void SetMovingRight(bool flag);			//設定螢幕往右移動
		void SetMovingUp(bool flag);			//設定螢幕往上移動
		void SetMovingDown(bool flag);			//設定螢幕往下移動
		void SetScreenPoint(CPoint);			//設定螢幕座標點
		void SetScreenViewPointByGrid(CPoint);
		void NormalizeScreen();					//
		CPoint GetScreenPoint();				//取得螢幕座標點
		int GridSizeX();						//取得2.5D格子的X軸(右下軸)
		int GridSizeY();						//取得2.5D格子地圖的Y軸(左下軸)
		int MapSizeX();							//取得MapSize(一格64)
		int MapSizeY();							//取得MapSize(一格64)
		CRect GridRect();
		CRect MapRect();
		void OnShow();							//將所有MapTile畫出
		void ShowMapTile();
		void ShowSprites();
		void ShowFog();
		CMapTile* GetMapTile(CPoint gridPoint);
		bool CanPutHere(CPoint mapPoint);
		bool CanPutHere(CRect rect);
		CMovingBitmap fog;
	private:
		int sx,sy;
		int sizeX,sizeY;
		bool isMovingLeft,isMovingUp,isMovingRight,isMovingDown;
		CGameMap();
		static CGameMap* map;
		CMapTile mapTile[MAX_SIDE][MAX_SIDE];
	};

}
#endif