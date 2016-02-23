#ifndef GUARD_PROJECTILE_OBJECT
#define GUARD_PROJECTILE_OBJECT

#include "StdAfx.h"
#include "AnimatedObject.h"
#include "Enemy.h"
#include "Tower.h"

class Projectile : public AnimatedObject
{
	enum ProjState { Charging, Traveling, Exploding, NonExisting };
	public:
		Projectile(std::string key, TextureManager&, Tower&, Enemy*, sf::Time);
		~Projectile();

		void update(sf::Time);
		void move();
		void explode();


	private:
		ProjState _pState;

		//Stats
		int _dmg;
		int _speed;

		//movement speed and frame speed
		sf::Int32 _movementTime;

		//direction projectile will head in
		std::unique_ptr<Enemy> _target;
};

#endif
