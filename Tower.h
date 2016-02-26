#ifndef GUARD_TOWER_H
#define GUARD_TOWER_H

#include "StdAfx.h"
#include "AnimatedObject.h"
#include "Enemy.h"


class Tower : public AnimatedObject
{
	enum Tstate { Building, Waiting, Firing, Upgrading };
	public:
		/*
		 *For upgraded towers
		 *Base is *10 then the added type is plused( (B * 10) + 1 )
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
		void place(float x, float y) { setPosition(x, y); _isPlaced = true; };
		void placing(sf::RenderWindow&);

		//checkers
		bool isPlaced() { return _isPlaced; };
		bool isFiring() { return _isFiring; };

		float getRadius() { return _radius; };
		float getDmg() { return _dmg; };

		int getTypeInt() { return (int)_type;};
		TowerType getType() { return _type;};
	private:
		bool _isPlaced;
		bool _isFiring;

		Tstate _tState;

		//Time to determine firerate
		sf::Int32 _fireTime;

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
