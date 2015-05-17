#ifndef CCONVERT_H
#define CCONVERT_H


namespace game_framework {
	////
	////CConvert
	////轉換三種座標系，
	////2D座標系：	螢幕座標
	////2.5D座標系：地圖座標、格子座標
	////限定函數
	class CConvert{
	public:
		static bool MapPointInRange(const CPoint&);
		static bool GridPointInRange(const CPoint&);
		static bool GridRectInRange(const CRect&);
		static void FitGridPoint(CPoint&);
		static void FitMapPoint(CPoint&);
		static void FitGridRect(CRect& rect);
		static CPoint GetGridPointByScreenPoint(CPoint);//輸入螢幕點得到格子座標
		static CPoint GetGridPointByMapPoint(CPoint);//輸入地圖座標得到格子座標
		static CPoint GetMapPointByScreenPoint(CPoint);//輸入螢幕座標得到地圖座標
		static CPoint GetMapPointByGridPoint(CPoint);//輸入格子座標得到地圖座標
		static CPoint GetScreenPointByGridPoint(CPoint);//輸入格子座標得到螢幕座標
		static CPoint GetScreenPointByMapPoint(CPoint);//輸入地圖座標得到螢幕座標

		static CPoint GetWorldPointByMapPoint(CPoint);//輸入地圖座標得到世界座標(map的sx,sy)
		static CPoint GetWorldPointByGridPoint(CPoint);//輸入格子座標得到世界座標(map的sx,sy)
	};
}
#endif