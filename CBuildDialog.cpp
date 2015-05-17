#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "mygame.h"
#include "CGameMap.h"
#include "CMouse.h"
#include "CConvert.h"
#include "CDialog.h"
#include "CBuildingBuilder.h"
#include "CBuildDialog.h"

namespace game_framework {
	void CBuildDialog::command(){
		if(sprite->Player()==CPlayer::GetPlayer()){
			if(sprite->Player()->ResourceTable()>=resourceTable){
				sprite->Player()->ResourceTable()-=resourceTable;
				Build();
			}else{
				CAudio::Instance()->Play(AUDIO_DEATH,false);
			}
		}
	}

	void CBuildDialog::SetSprite(CSprite* sprite){this->sprite = sprite;}
	
	void CBuildDialog::OnShow(){
		CDialog::OnShow();
		CMouse* mouse = CMouse::GetMouse();
		if(this->PtInRect(mouse->Point())){
			char woodStr[100]="",foodStr[100]="",stoneStr[100]="",goldStr[100]="";
			if(resourceTable.Wood()!=0){
				sprintf(woodStr,"木頭:%d ",resourceTable.Wood());
			}
			if(resourceTable.Food()!=0){
				sprintf(foodStr,"食物:%d ",resourceTable.Food());
			}
			if(resourceTable.Gold()!=0){
				sprintf(goldStr,"金礦:%d ",resourceTable.Gold());
			}
			if(resourceTable.Stone()!=0){
				sprintf(stoneStr,"石頭:%d ",resourceTable.Stone());
			}
			char output[100];
			
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f,*fp;
			f.CreatePointFont(100,"Times New Roman");	// 產生 font f; 160表示16 point的字
			fp=pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0,0,0));
			pDC->SetTextColor(RGB(255,255,0));
			sprintf(output,"%s%s%s%s",woodStr,foodStr,goldStr,stoneStr);
			pDC->TextOutA(mouse->Point().x,mouse->Point().y-20,output);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

		}
	}
}