#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#ifndef GAMELIB_H
#define GAMELIB_H
#include "gamelib.h"
#endif
#include <set>
#include "CSprite.h"
#include "CPlayer.h"
#include "mygame.h"

namespace game_framework {
	CPlayer* CPlayer::player=NULL;
	CPlayer* CPlayer::npc=NULL;
	CPlayer* CPlayer::nature=NULL;

	CPlayer* CPlayer::GetNPC(){
		if(npc==NULL){
			npc = new CPlayer();
			npc->mark.LoadBitmapA("Bitmaps/Players/npc.bmp");
		}
		return npc;
	}
	CPlayer* CPlayer::GetPlayer(){
		if(player==NULL){
			player = new CPlayer();
			player->mark.LoadBitmapA("Bitmaps/Players/player.bmp");
		}
		return player;
	}
	CPlayer* CPlayer::GetNature(){
		if(nature==NULL){
			nature = new CPlayer();
			nature->mark.LoadBitmapA("Bitmaps/Players/nature.bmp");
		}
		return nature;
	}

	void CPlayer::Dispose(){
		delete player;
		delete npc;
		delete nature;
		player = npc = nature = NULL;
	}

	void CPlayer::AddDieSprite(CSprite* sprite){
		dieSprites.insert(sprite);
	}
	void CPlayer::EraseSprites(){
		set<CSprite*>::iterator it;
		for(it = dieSprites.begin();it!=dieSprites.end();it++){
			delete (*it);
			sprites.erase(*it);
		}
		dieSprites.clear();
	}
	CResourceTable& CPlayer::ResourceTable(){return resourceTable;}
	
	set<CSprite*>& CPlayer::Sprites(){return sprites;}

	CPlayer::CPlayer(){
		this->sprites.clear();
		resourceTable = CResourceTable(0,200,0,0);
	}
	CPlayer::~CPlayer(){
		//清除玩家的所有物件(包含建築、單位)，
		set<CSprite*>::iterator it;
		for(it = this->sprites.begin();it!=this->sprites.end();it++){
			delete (*it);
		}
		this->sprites.clear();
	}
	void CPlayer::ShowBitmap(CPoint screenPoint){
		mark.SetTopLeft(screenPoint.x,screenPoint.y);
		mark.ShowBitmap();
	}
}