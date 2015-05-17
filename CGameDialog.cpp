#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameDialog.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CGameDialog，一個接受範圍性滑鼠事件的視窗類別
/////////////////////////////////////////////////////////////////////////////
	void CGameDialog::OnShow()
	{
		if(bmp.IsBitmapLoaded()){
			bmp.SetTopLeft(left,top);
			bmp.ShowBitmap();
		}
	}
}