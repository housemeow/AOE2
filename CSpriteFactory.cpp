#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <set>
#include "CSprite.h"
#include "CConvert.h"
#include "CSelectionPanel.h"
#include "CDialog.h"
#include "CSprite.h"
#include "mygame.h"
#include "CSpriteFactory.h"
#include "CVillager.h"
#include "CFruit.h"
#include "CTownCenter.h"

namespace game_framework 
{
	CSprite* CVillagerFactory::CreatSprite()
	{
		return new CVillager();
	}
	CSprite* CFruitFactory::CreatSprite()
	{
		return new CFruit();
	}
	CSprite* CTownCenterFactory::CreatSprite()
	{
		return new CTownCenter();
	}
}