#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameDialog.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CGameDialog�A�@�ӱ����d��ʷƹ��ƥ󪺵������O
/////////////////////////////////////////////////////////////////////////////
	void CGameDialog::OnShow()
	{
		if(bmp.IsBitmapLoaded()){
			bmp.SetTopLeft(left,top);
			bmp.ShowBitmap();
		}
	}
}