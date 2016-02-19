#ifndef GUARD_TOWER_H
#define GUARD_TOWER_H

#include "StdAfx.h"
#include "TextureManager.h"
#include "VisibleObject.h"
#include "Enemy.h"


class Tower : public VisibleObject
{
	public:
		/*
		 *Base is timesd by 10 then the added type is plused( (B * 10) + 1 )
		 */
		enum TowerType
		{
			Dmg=1, DmgDmg=11, DmgSpd=12, DmgBnc=13,
			Spd=2, SpdDmg=21, SpdSpd=22, SpdBnc=23,
			Bnc=3, BncDmg=31, BncSpd=32, BncBnc=33
		};

		Tower(int type, TextureManager& textures, std::string key);

		void update(sf::Time);
		void fire();

		void loadFromBaseType(TextureManager& textures);
		void setStatsFromType(int);
		void place() { _isPlaced = true; };

		TowerType getNewTowerType(TowerType base, TowerType upg);

		//checkers
		bool isPlaced() { return _isPlaced; };
		bool isInRange();

	private:
		bool _isPlaced;

		//Clock to determin when shots can be fired
		sf::Clock _fClock;

		//Stats
		int _radius;
		int _dmg;
		int _fireRate;

		//info
		TowerType _type;

		//projectile info
		int _shotNr;
};

#endif
