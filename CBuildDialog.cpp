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
				sprintf(woodStr,"���Y:%d ",resourceTable.Wood());
			}
			if(resourceTable.Food()!=0){
				sprintf(foodStr,"����:%d ",resourceTable.Food());
			}
			if(resourceTable.Gold()!=0){
				sprintf(goldStr,"���q:%d ",resourceTable.Gold());
			}
			if(resourceTable.Stone()!=0){
				sprintf(stoneStr,"���Y:%d ",resourceTable.Stone());
			}
			char output[100];
			
			CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
			CFont f,*fp;
			f.CreatePointFont(100,"Times New Roman");	// ���� font f; 160���16 point���r
			fp=pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(RGB(0,0,0));
			pDC->SetTextColor(RGB(255,255,0));
			sprintf(output,"%s%s%s%s",woodStr,foodStr,goldStr,stoneStr);
			pDC->TextOutA(mouse->Point().x,mouse->Point().y-20,output);
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

		}
	}
}