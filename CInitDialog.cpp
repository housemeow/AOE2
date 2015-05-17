#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CInitDialog.h"
namespace game_framework {
	CInitScreenDialog* CInitScreenDialog::initScreenDialog = NULL;
	
	CInitScreenDialog* CInitScreenDialog::GetInitScreenDialog(){
		if(initScreenDialog==NULL){
			initScreenDialog = new CInitScreenDialog();
		}
		return initScreenDialog;
	}
		
	void CInitScreenDialog::Dispose(){
		delete initScreenDialog;
		initScreenDialog=NULL;
		CStartDialog::Dispose();
		CHelpDialog::Dispose();
		CEndDialog::Dispose();
	}
	CInitScreenDialog::CInitScreenDialog(){
		AddGameDialog(CStartDialog::GetStartDialog());
		AddGameDialog(CHelpDialog::GetHelpDialog());
		AddGameDialog(CEndDialog::GetEndDialog());
	}
	CInitScreenDialog::~CInitScreenDialog(){}











	CStartDialog* CStartDialog::startDialog=NULL;
	CEndDialog* CEndDialog::endDialog=NULL;
	CHelpDialog*CHelpDialog::helpDialog=NULL;
	CStartDialog::CStartDialog()
	{
		LoadBitmap();
		CPoint point=CPoint(SIZE_X/3,SIZE_Y/2+100);
		SetRect(point,point+CPoint(bmp.Width(),bmp.Height()));
	}
	CStartDialog* CStartDialog::GetStartDialog()
	{
		if(startDialog==NULL)
		{
			startDialog=new CStartDialog();
		}
		return startDialog;
	}
	void CStartDialog::Dispose(){delete startDialog;startDialog=NULL;}
	void CStartDialog::LoadBitmap(){bmp.LoadBitmapA("Bitmaps/UI/start.bmp",0);}
	void CStartDialog::onShow(){bmp.SetTopLeft(SIZE_X/3,SIZE_Y/2+100);bmp.ShowBitmap();}
	CStartDialog::~CStartDialog(){}
	void CStartDialog::OnLeftDown(const CMouseState& state){

	}
	CEndDialog::CEndDialog()
	{
		LoadBitmap();
		CPoint point=CPoint(SIZE_X/3,SIZE_Y/2+100+100);
		SetRect(point,point+CPoint(bmp.Width(),bmp.Height()));
	}
	CEndDialog* CEndDialog::GetEndDialog()
	{
		if(endDialog==NULL)
		{
			endDialog=new CEndDialog();
		}
		return endDialog;
	}
	void CEndDialog::Dispose(){delete endDialog;endDialog=NULL;}
	void CEndDialog::LoadBitmap(){bmp.LoadBitmapA("Bitmaps/UI/end.bmp",0);}
	void CEndDialog::onShow(){bmp.SetTopLeft(SIZE_X/3,SIZE_Y/2+100+100);bmp.ShowBitmap();}
	CEndDialog::~CEndDialog(){}
	CHelpDialog::CHelpDialog()
	{
		LoadBitmap();
		CPoint point=CPoint(SIZE_X/3,SIZE_Y/2+40+100);
		SetRect(point,point+CPoint(bmp.Width(),bmp.Height()));
	}
	CHelpDialog* CHelpDialog::GetHelpDialog()
	{
		if(helpDialog==NULL)
		{
			helpDialog=new CHelpDialog();
		}
		return helpDialog;
	}
	void CHelpDialog::Dispose(){delete helpDialog;helpDialog=NULL;}
	void CHelpDialog::LoadBitmap(){bmp.LoadBitmapA("Bitmaps/UI/help.bmp",0);}
	void CHelpDialog::onShow(){bmp.SetTopLeft(SIZE_X/3,SIZE_Y/2+40+100);bmp.ShowBitmap();}
	CHelpDialog::~CHelpDialog(){}
}