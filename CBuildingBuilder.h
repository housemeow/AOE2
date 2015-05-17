#ifndef CBUILDINGBUILDER_H
#define CBUILDINGBUILDER_H

#include "CSprite.h"
#include "CBuilding.h"

namespace game_framework {
	class CBuildingBuilder{
	public:
		static CBuildingBuilder* GetBuildingBuilder();
		static void ReleaseBuildingBuilder();
		void SetBuilding(CBuilding* building);
		void PutBuilding();
		void CancelBuilding();
		void OnShow();
		void OnMove();
		bool IsBuilding();
	private:
		static CBuildingBuilder* buildingBuilder;
		CBuildingBuilder();
		~CBuildingBuilder();
		CBuilding* building;
	};
}
#endif