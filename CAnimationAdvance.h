#ifndef CANIMATIONADVANCE_H
#define CANIMATIONADVANCE_H


namespace game_framework 
{
	class CAnimationAdvance
	{
		public:
			CAnimationAdvance();
			void SetAnimation(CAnimation *);
			void SetTopLeft(int left,int top);
			void OnMove();
			void OnShow();
			CMovingBitmap* GetBitmap();
		private:
			list<CMovingBitmap>::iterator	bmp_iter;
			CAnimation *animation;
			int delay_counter;
	};
}

#endif