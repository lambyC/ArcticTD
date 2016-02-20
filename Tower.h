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
		void fire(sf::Time);

		void loadFromBaseType(TextureManager& textures);
		void setStatsFromType(int);
		void place() { _isPlaced = true; };
		void placing(sf::RenderWindow&);

		TowerType getNewTowerType(TowerType base, TowerType upg);

		//checkers
		bool isPlaced() { return _isPlaced; };
		bool isFiring() { return _isFiring; };
		bool isInRange();

		float getRadius() { return _radius; };

	private:
		bool _isPlaced;
		bool _isFiring;

		//Time to determine firerate
		sf::Int32 _fireTime;
		sf::Int32 _frameTime;

		//Stats
		float _radius;
		int _dmg;
		int _fireRate;

		//info
		TowerType _type;

		//projectile info
		int _shotNr;
};

#endif
