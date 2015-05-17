#ifndef CCONVERT_H
#define CCONVERT_H


namespace game_framework {
	////
	////CConvert
	////�ഫ�T�خy�Шt�A
	////2D�y�Шt�G	�ù��y��
	////2.5D�y�Шt�G�a�Ϯy�СB��l�y��
	////���w���
	class CConvert{
	public:
		static bool MapPointInRange(const CPoint&);
		static bool GridPointInRange(const CPoint&);
		static bool GridRectInRange(const CRect&);
		static void FitGridPoint(CPoint&);
		static void FitMapPoint(CPoint&);
		static void FitGridRect(CRect& rect);
		static CPoint GetGridPointByScreenPoint(CPoint);//��J�ù��I�o���l�y��
		static CPoint GetGridPointByMapPoint(CPoint);//��J�a�Ϯy�бo���l�y��
		static CPoint GetMapPointByScreenPoint(CPoint);//��J�ù��y�бo��a�Ϯy��
		static CPoint GetMapPointByGridPoint(CPoint);//��J��l�y�бo��a�Ϯy��
		static CPoint GetScreenPointByGridPoint(CPoint);//��J��l�y�бo��ù��y��
		static CPoint GetScreenPointByMapPoint(CPoint);//��J�a�Ϯy�бo��ù��y��

		static CPoint GetWorldPointByMapPoint(CPoint);//��J�a�Ϯy�бo��@�ɮy��(map��sx,sy)
		static CPoint GetWorldPointByGridPoint(CPoint);//��J��l�y�бo��@�ɮy��(map��sx,sy)
	};
}
#endif