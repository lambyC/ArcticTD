#ifndef GUARD_ENEMY_H
#define GUARD_ENEMY_H

#include "StdAfx.h"
#include "VisibleObject.h"
#include "TextureManager.h"

class Enemy : public VisibleObject
{
	public:
		enum EnemyType
		{
			Adult_P, Cyb_P, Baby_P, Giant_P 
		};
		enum Direction { Right, Up, Left, Down};

		Enemy(EnemyType, TextureManager&, const std::string& key, sf::Time);
		~Enemy();

		void update(sf::Time);
		void move();
		void kill();

		void loadEnemyStatsFromFile(const EnemyType&);
		void loadEnemyTextureFromFile(TextureManager&);

		void setSpawnLocation();
		void setMovementPath(std::vector<sf::Vector2f> path) { _path = path; };

		int getSpawnDelay() { return _spawnDelay; };

		bool isAlive() { return _isAlive; };

	private:
		//moving direction, to point in vector path;
		int _point;
		std::vector<sf::Vector2f> _path;

		bool _isAlive;

		//default size is 64
		sf::IntRect _size;

		//default is 3 frames of animation
		int _maxFrames;
		//frame direction
		bool _isRight;
		//current frame
		sf::IntRect _frame;
		//direction enemy is moving, determins animation row used;
		Direction _direction;

		//
		EnemyType _type;
		std::string _key;

		//Clock
		sf::Int32 _moveTime;
		sf::Int32 _frameTime;

		//Stats
		int _initialHealth;
		int _health;
		int _speed;
		int _spawnDelay;

};

#endif
