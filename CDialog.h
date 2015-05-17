#ifndef CDIALOG_H
#define CDIALOG_H
#include <vector>
#include "CSprite.h"
namespace game_framework {
	class CDialog:public CRect
	{
		public:
			  CMovingBitmap pic;
			  vector<CDialog*> subDialog; 
		public:
			CDialog(){};
			virtual ~CDialog(){};
			virtual void LoadBitmap(){};
			virtual void OnShow();
			virtual void command(){};
			bool CheckThePointIn(CPoint);
	};
	class CFunctionDialog:public CDialog
	{
	public:
		static CFunctionDialog* GetFunctionDialog();
		static void Dispose();
		void ClearSubDialog();
		void SetSubDialog();
		void AddSubDialog(CDialog*);
		void ShowSubDialog();
		void command();
		CSprite* topselectedObject;
	private:
		static CFunctionDialog* functionDialog;
		CFunctionDialog();
		~CFunctionDialog();

	};
	class CObjectContainDialog:public CDialog
	{
	public:
		CObjectContainDialog();
		~CObjectContainDialog();
		void SelectedObjects();
		void SetTopSelectSprite();
		void ShowSubDialog();
		void command();
		void OnShow();
		CSprite * GetTopSelectSprite(){return topselectedSprite;}
	private:
		CSprite* topselectedSprite;
	};

	class CSmallMapDialog:public CDialog
	{
	public:
		bool IsLeftMouseDown;
		CRect SmallMapView;
		CSmallMapDialog();
		~CSmallMapDialog();
		void ShowSmallMap();
		void command();
	private:
		CMovingBitmap smallmap;
		CMovingBitmap bottom;
		CMovingBitmap buffer;
		CMovingBitmap *nature;
		CMovingBitmap *npc;
		CMovingBitmap *player;
	};
	class CPlayerDialog:public CDialog
	{
	public:
		CPlayerDialog();
		~CPlayerDialog();
		void command();
		void OnShow();
	};
	class CMapDialog:public CDialog
	{
	public:
		CMapDialog();
		~CMapDialog();
		void command();
	};
	class CScreenDialog:public CDialog
	{
	public:
		static CScreenDialog* GetScreenDialog();
		static void Dispose();
		void command();
		CFunctionDialog* FunctionDialog();

		CObjectContainDialog ObjectContainDialog;
		CSmallMapDialog SmallMapDialog;
		CPlayerDialog PlayerDialog;
		CMapDialog MapDialog;
	private:
		static CScreenDialog* screenDialog;
		CScreenDialog();
		~CScreenDialog();

	};
}

#endif