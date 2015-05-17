#ifndef CRESOURCETABLE_H
#define CRESOURCETABLE_H


namespace game_framework {
	class CResourceTable{
	public:
		CResourceTable();
		CResourceTable(int wood,int food,int gold,int stone);
		void Reset();
		int Food() const;
		int Wood() const;
		int Stone() const;
		int Gold() const;
		CResourceTable operator +(const CResourceTable& resource);
		CResourceTable operator -(const CResourceTable& resource);
		void operator +=(const CResourceTable& resource);
		void operator -=(const CResourceTable& resource);
		bool operator >=(const CResourceTable& resource);
	private:
		int food;
		int wood;
		int stone;
		int gold;
	};
}
#endif