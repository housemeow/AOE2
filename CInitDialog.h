#ifndef CINITDIALOG_H
#define CINITDIALOG_H
#include "CMultiGameDialog.h"
namespace game_framework {
	class CInitScreenDialog:public CMultiGameDialog{
	public:
		static CInitScreenDialog* GetInitScreenDialog();
		void static Dispose();
	private:
		static CInitScreenDialog* initScreenDialog;
		CInitScreenDialog();
		~CInitScreenDialog();
	};


	class CStartDialog:public CGameDialog
	{
		public:
			static CStartDialog* GetStartDialog();
			CStartDialog();
			~CStartDialog();
			void LoadBitmap();
			void OnLeftDown(const CMouseState& state);
			void onShow();
			static void Dispose();
		private:
			static CStartDialog* startDialog;
			
	};
	class CHelpDialog:public CGameDialog
	{	
		public:
			static CHelpDialog* GetHelpDialog();
			CHelpDialog();
			~CHelpDialog();
			void LoadBitmap();
			void onShow();
			static  void Dispose();
		private:
			static CHelpDialog* helpDialog;
			
	};
	class CEndDialog:public CGameDialog
	{
		public:
			static CEndDialog* GetEndDialog();
			CEndDialog();
			~CEndDialog();
			void LoadBitmap();
			void onShow();
			static void Dispose();
		private:
			static CEndDialog* endDialog;
			
	};
}
#endif