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
		static void InitMap(int side);		//��l��Map����A�̦hMAX_SIDE*MAX_SIDE���a��
		static CGameMap* GetMap();				//���oGameMap������A�p�G�S���N�гy�@�ӷs��
		static void ReleaseMap();				//����ثe��GameMap

		void OnMove();							//���ʦa�ϡA�o��|���ù��y�Юշ�
		void SetMovingLeft(bool flag);			//�]�w�ù���������
		void SetMovingRight(bool flag);			//�]�w�ù����k����
		void SetMovingUp(bool flag);			//�]�w�ù����W����
		void SetMovingDown(bool flag);			//�]�w�ù����U����
		void SetScreenPoint(CPoint);			//�]�w�ù��y���I
		void SetScreenViewPointByGrid(CPoint);
		void NormalizeScreen();					//
		CPoint GetScreenPoint();				//���o�ù��y���I
		int GridSizeX();						//���o2.5D��l��X�b(�k�U�b)
		int GridSizeY();						//���o2.5D��l�a�Ϫ�Y�b(���U�b)
		int MapSizeX();							//���oMapSize(�@��64)
		int MapSizeY();							//���oMapSize(�@��64)
		CRect GridRect();
		CRect MapRect();
		void OnShow();							//�N�Ҧ�MapTile�e�X
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