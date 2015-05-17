#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameMap.h"
#include "CMouse.h"
#include "CConvert.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "CBuildingBuilder.h"
#include "CTownCenter.h"
#include "CBuildTownCenter.h"
#include "CVillager.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CDialog，所有Dialog的基底類別
/////////////////////////////////////////////////////////////////////////////
	bool CDialog::CheckThePointIn(CPoint point)
	{
		if(this->PtInRect(point))//如果點在裡面
		{
			this->command();//執行他的方法
			vector<CDialog*>::iterator ptr;
			for(ptr=subDialog.begin();ptr!=subDialog.end();ptr++)
			{//執行偵測subDialog
			
					(*ptr)->CheckThePointIn(point);
			}
			return true;
		}else
		{
			return false;
		}
	}
	void CDialog::OnShow()
	{
		this->pic.SetTopLeft(this->left,this->top);
		this->pic.ShowBitmap();
	}


/////////////////////////////////////////////////////////////////////////////
// CScreenDialog，整個螢幕的Dialog，用來管理所有的對話框
// 如PlayerDialog, MapDialog, FunctionDialog, ObjectContainDialog, SmallMapDialog
/////////////////////////////////////////////////////////////////////////////
	CScreenDialog* CScreenDialog::screenDialog=NULL;
	CScreenDialog::CScreenDialog()
	{
		this->SetRect(-1,-1,SIZE_X,SIZE_Y);
		subDialog.push_back(&PlayerDialog);
		subDialog.push_back(&MapDialog);
		subDialog.push_back(FunctionDialog());
		subDialog.push_back(&ObjectContainDialog);
		subDialog.push_back(&SmallMapDialog);
	}
	CScreenDialog::~CScreenDialog()
	{
		subDialog.clear();
	}
	void CScreenDialog::command()
	{
		TRACE("ScreenDialog\n");
	}
	CScreenDialog* CScreenDialog::GetScreenDialog()
	{
		if(screenDialog==NULL)
		{
			screenDialog=new CScreenDialog();
		}
		return screenDialog;
	}
	void CScreenDialog::Dispose()
	{
		delete screenDialog;
		screenDialog=NULL;
		CFunctionDialog::Dispose();
	}
	
	CFunctionDialog* CScreenDialog::FunctionDialog(){return CFunctionDialog::GetFunctionDialog();}


/////////////////////////////////////////////////////////////////////////////
// CPlayerDialog，最上方玩家資訊的Dialog
/////////////////////////////////////////////////////////////////////////////
	CPlayerDialog::CPlayerDialog()
	{
		this->SetRect(0,0,SIZE_X,24);
	}
	CPlayerDialog::~CPlayerDialog()
	{

	}
	void CPlayerDialog::command()
	{
		TRACE("PlayerDialog\n");
	}
	void CPlayerDialog::OnShow(){
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f,*fp;
		f.CreatePointFont(100,"Times New Roman");	// 產生 font f; 160表示16 point的字
		fp=pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,255));
		char str[80];
		CPlayer* player = CPlayer::GetPlayer();
		sprintf(str,"%d",player->ResourceTable().Wood());
		pDC->TextOut(30,3,str);
		sprintf(str,"%d",player->ResourceTable().Food());
		pDC->TextOut(106,3,str);
		sprintf(str,"%d",player->ResourceTable().Gold());
		pDC->TextOut(182,3,str);
		sprintf(str,"%d",player->ResourceTable().Stone());
		pDC->TextOut(258,3,str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

/////////////////////////////////////////////////////////////////////////////
// CFunctionDialog，左下角功能按鈕的Dialog
/////////////////////////////////////////////////////////////////////////////
	CFunctionDialog* CFunctionDialog::functionDialog = NULL;

	CFunctionDialog::CFunctionDialog()
	{
		this->SetRect(0,SIZE_Y-137,220,SIZE_Y);
	}
	CFunctionDialog::~CFunctionDialog()
	{
		this->ClearSubDialog();
	}
	CFunctionDialog* CFunctionDialog::GetFunctionDialog(){
		if(functionDialog==NULL){
			functionDialog = new CFunctionDialog();
		}
		return functionDialog;
	}
	void CFunctionDialog::Dispose(){
		delete functionDialog;
		functionDialog = NULL;
	}

	void CFunctionDialog::ClearSubDialog()
	{
		vector<CDialog*>::iterator itr;
		for(itr=subDialog.begin();itr!=subDialog.end();itr++)
		{
			delete (*itr);
		}
		subDialog.clear();
		TRACE("delete functiondialog\n");
	}
	void CFunctionDialog::SetSubDialog()
	{
			CScreenDialog* sd = CScreenDialog::GetScreenDialog();
			if(sd->ObjectContainDialog.GetTopSelectSprite()!=NULL)
			{
				sd->FunctionDialog()->ClearSubDialog();
				sd->ObjectContainDialog.GetTopSelectSprite()->FunctionDialogComposite();
			}else
			{
				sd->FunctionDialog()->ClearSubDialog();
			}
			
	}
	void CFunctionDialog::AddSubDialog(CDialog *dialog)
	{
		dialog->SetRect(this->left+(subDialog.size()%5)*dialog->pic.Width(),this->top+(subDialog.size()/5)*dialog->pic.Height(),
			this->left+(subDialog.size()%5+1)*dialog->pic.Width(),this->top+(subDialog.size()/5+1)*dialog->pic.Height());
		subDialog.push_back(dialog);
	}
	void CFunctionDialog::ShowSubDialog()
	{
		vector<CDialog*>::iterator itr;
		for(int i=(int)subDialog.size()-1;i>=0;i--){
			subDialog[i]->OnShow();
		}
	}
	void CFunctionDialog::command()
	{
		TRACE("FunctionDialog\n");	
	}





/////////////////////////////////////////////////////////////////////////////
// CObjectContainDialog，正下方顯示目前選取物件的Dialog
/////////////////////////////////////////////////////////////////////////////
	void CObjectContainDialog::SetTopSelectSprite()
	{
		set<CSprite*>::iterator itr;
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		itr=panel->SelectedSprites().begin();
		if(itr!=panel->SelectedSprites().end())
		{
			topselectedSprite=(*itr);//先暫訂第一個sprite為主要的功能表，以後在這邊寫權重選擇
		}else if(panel->SelectedSprites().empty())//如果沒選到東西
		{
			topselectedSprite=NULL;
			//把subDialog都清空
		}
	}
	CObjectContainDialog::CObjectContainDialog()
	{
		this->SetRect(220,SIZE_Y-137,530,SIZE_Y);
	}
	void CObjectContainDialog::SelectedObjects()
	{
		subDialog.clear();
		set<CSprite*>::iterator itr;
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		subDialog.clear();
		itr=panel->SelectedSprites().begin();
		SetTopSelectSprite();
		for(itr=panel->SelectedSprites().begin();itr!=panel->SelectedSprites().end();itr++)
		{
			subDialog.push_back((*itr)->IconDialog());
		}
		
	}
	void CObjectContainDialog::ShowSubDialog()
	{
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		set<CSprite*>::iterator it;

		int count=0;
		for(it = panel->SelectedSprites().begin();it!=panel->SelectedSprites().end();it++){
			CSprite::CIconDialog* id = (*it)->IconDialog();
			id->SetRect(this->left+(count%9)*id->pic.Width(),this->top+(count/9)*id->pic.Height(),
				this->left+(count%9+1)*id->pic.Width(),this->top+(count/9+1)*id->pic.Height());
			id->OnShow();
			count++;
		}
	}
	void CObjectContainDialog::command()
	{
		TRACE("ObjectContainDialog\n");
	}
	void CObjectContainDialog::OnShow(){
		CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
		if(panel->SelectedSprites().size()==1){
			set<CSprite*>::iterator it = panel->SelectedSprites().begin();
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f,*fp;
			f.CreatePointFont(150,"Times New Roman");	// 產生 font f; 160表示16 point的字
			fp=pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0,0,0));
			pDC->SetTextColor(RGB(255,255,255));
			char str[80];
			sprintf(str,"HP: %d/%d",(*it)->HP(),(*it)->MaxHP());
			pDC->TextOut(250,530,str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}
	}
	CObjectContainDialog::~CObjectContainDialog()
	{
		
	}
/////////////////////////////////////////////////////////////////////////////
// CMapDialog，中間遊戲地圖的Dialog
/////////////////////////////////////////////////////////////////////////////
	CMapDialog::CMapDialog()
	{
		this->SetRect(0,24,SIZE_X,SIZE_Y-137);
	}
	CMapDialog::~CMapDialog()
	{

	}
	void CMapDialog::command()
	{
		TRACE("MapDialog\n");
	}


/////////////////////////////////////////////////////////////////////////////
// SmallMapDialog，顯示小地圖資訊的Dialog，接受左鍵移動視角，右鍵鎖定目標
/////////////////////////////////////////////////////////////////////////////
	CSmallMapDialog::CSmallMapDialog()
	{
		IsLeftMouseDown=false;
		this->SetRect(530,SIZE_Y-137,SIZE_X,SIZE_Y);
		bottom.LoadBitmapA("Bitmaps/UI/bottom1.bmp");
		smallmap.LoadBitmapA("Bitmaps/UI/bottom.bmp");
		nature=new CMovingBitmap();
		nature->LoadBitmapA("Bitmaps/SmallMap/nature.bmp");
		player=new CMovingBitmap();
		player->LoadBitmapA("Bitmaps/SmallMap/player.bmp");
		npc=new CMovingBitmap();
		npc->LoadBitmapA("Bitmaps/SmallMap/npc.bmp");
	}
	CSmallMapDialog::~CSmallMapDialog()
	{
		delete nature;
		delete player;
		delete npc;
	}
	void CSmallMapDialog::command()
	{
		CGameMap *map= CGameMap::GetMap();
		CMouse *mouse=CMouse::GetMouse();
		if(mouse->LeftIsDown())
		{
			CPoint Grid=
			CPoint(
			((mouse->Point().x-left)-Width()/2)*map->GridSizeX()/Width()*(64)+(map->GridSizeX()-map->GridSizeY())*32/2-400,
			((mouse->Point().y-top)-Height()/2)*map->GridSizeY()/Height()*(32)+(map->GridSizeY()+map->GridSizeX())*16/2-220);
			map->SetScreenPoint(Grid);
		}
		if(mouse->RightIsDown())
		{
			CPlayer*player;
			player = CPlayer::GetPlayer();
			CPoint Grid=
			CPoint(
			((mouse->Point().x-left)-Width()/2)*map->GridSizeX()/Width()*(64) + (map->GridSizeX()-map->GridSizeY())*32/2,
			((mouse->Point().y-top)-Height()/2)*map->GridSizeY()/Height()*(32)+ (map->GridSizeY()+map->GridSizeX())*16/2);
			
			CPoint mapPoint;

			mapPoint.x=Grid.y*2+Grid.x;
			mapPoint.y=Grid.y*2-Grid.x;

			CTarget target=CTarget(mapPoint);
			CSelectionPanel* panel = CSelectionPanel::GetSelectionPanel();
			set<CSprite*>::iterator it;
			for(it = panel->SelectedSprites().begin(); it!=panel->SelectedSprites().end();it++){
				if((*it)->Player()==player){//只可操控自己的角色
					if((*it)->Target().IsSprite()){
						(*it)->Target().Sprite()->targetedSprites.erase(*it);
					}
					(*it)->SetTarget(target);
				}
			}
		}
	}
	void CSmallMapDialog::ShowSmallMap()
	{
		CGameMap *map=CGameMap::GetMap();
		
		bottom.SetTopLeft(0,0);

		

		bottom.ShowBitmap(smallmap);
		//smallmap=bottom;
		CSize size(5,5);
		for(int x=0;x < map->GridSizeX();x+=3){
			for(int y=0;y < map->GridSizeY();y+=3){
				CRect rect = CRect(CPoint(x,y),size);
				CConvert::FitGridRect(rect);
				for(int gx=rect.left;gx<rect.right;gx++){
					for(int gy=rect.top;gy<rect.bottom;gy++){
						CPoint Grid=CPoint(gx,gy);
						CMapTile* mapTile = map->GetMapTile(CPoint(gx,gy));
						if(mapTile->IsEmpty() || !mapTile->IsExplored()){
							continue;
						}
						CSprite* sprite = *(mapTile->Sprites().begin());
						if(sprite->Player()==CPlayer::GetPlayer()){
							player->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
									(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
							player->ShowBitmap(smallmap);
							gx = rect.right;
							gy = rect.bottom;
						}else if(sprite->Player()==CPlayer::GetNPC()){
							if(mapTile->VisionCount()>0){
								npc->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
												(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
								npc->ShowBitmap(smallmap);
								gx = rect.right;
								gy = rect.bottom;
							}
						}else if(sprite->Player()==CPlayer::GetNature()){
							nature->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
											(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
							nature->ShowBitmap(smallmap);
							gx = rect.right;
							gy = rect.bottom;
						}
					}
				}
			}
		}
		//for(int x=0;x < map->GridSizeX();x++)
		//{
		//	for(int y=0;y < map->GridSizeY();y++)
		//	{
		//		if(!map->GetMapTile(CPoint(x,y))->IsEmpty() && map->GetMapTile(CPoint(x,y))->VisionCount()>0)
		//		{
		//			if(x>=143){
		//				TRACE("");
		//			}
		//			CPoint Grid=CPoint(x,y);
		//			//CPoint Point=Grid;
		//			CPoint Point=CPoint(Grid.x -(map->GridSizeX()-map->GridSizeY())*32/2*Width()/map->GridSizeX()/64 ,
		//			Grid.y  -(map->GridSizeY()+map->GridSizeX())*16/2/Height()/map->GridSizeY()/32);

		//			//player->SetTopLeft(Width()/2+530+(Point.x-Point.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
		//							//(Point.x+Point.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
		//			set<CSprite*> sprites = map->GetMapTile(CPoint(x,y))->Sprites();
		//			set<CSprite*>::iterator ptr;
		//			ptr=sprites.begin();
		//			if((*ptr)->Player() == CPlayer::GetPlayer())
		//			{
		//				player->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
		//							(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
		//				player->ShowBitmap(smallmap);
		//				x+=3;
		//				y+=3;
		//				if(!(x<map->GridSizeX())){
		//					break;
		//				}
		//			}else if((*ptr)->Player() == CPlayer::GetNPC()){
		//				CMapTile* mapTile = map->GetMapTile((*ptr)->GridPoint());
		//				if(mapTile->IsExplored() && mapTile->VisionCount()>0){
		//					npc->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
		//									(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
		//					npc->ShowBitmap(smallmap);
		//					x+=1;
		//					y+=1;
		//					if(!(x<map->GridSizeX())){
		//						break;
		//					}
		//				}
		//			}else if((*ptr)->Player() == CPlayer::GetNature()){
		//				CMapTile* mapTile = map->GetMapTile((*ptr)->GridPoint());
		//				if(mapTile->IsExplored()){
		//					nature->SetTopLeft(Width()/2+530+(Grid.x-Grid.y)*2*Width()/(map->GridSizeX()+map->GridSizeY())/2,
		//									(Grid.x+Grid.y)*Height()/(map->GridSizeX()+map->GridSizeY()));
		//					nature->ShowBitmap(smallmap);
		//					x+=1;
		//					y+=1;
		//					if(!(x<map->GridSizeX())){
		//						break;
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
		smallmap.SetTopLeft(0,SIZE_Y-bottom.Height());
		smallmap.ShowBitmap();
	}
}