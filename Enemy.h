#ifndef GUARD_ENEMY_H
#define GUARD_ENEMY_H

#include "StdAfx.h"
#include "AnimatedObject.h"
#include "TextureManager.h"

class Enemy : public AnimatedObject
{
	enum Direction { Up, Right, Down, Left };
	enum Estate { Alive, Action, Dying };
	public:
		enum EnemyType
		{
			Adult_P, Cyb_P, Baby_P, Giant_P 
		};

		Enemy(EnemyType, TextureManager&, const std::string& key, sf::Time);
		~Enemy();

		void update(sf::Time);
		void move();
		void kill();

		void loadEnemyStatsFromFile(const EnemyType&);
		void loadEnemyTextureFromFile(TextureManager&);

		void setSpawnLocation();
		void setMovementPath(std::vector<sf::Vector2f> path) { _path = path; };


		void damage(int);
		void preDamage(int);

		int getSpawnDelay() { return _spawnDelay; };
		int getHealth() { return _health; };
		int getPreHealth() { return _preHealth; };

	private:
		//moving direction, to point in vector path;
		int _point;
		std::vector<sf::Vector2f> _path;

		Estate _eState;
		EnemyType _type;

		//moving
		sf::Int32 _moveTime;

		//Stats
		float _initialHealth;
		float _health;
		float _preHealth;
		int _speed;
		int _spawnDelay;
};

#endif
