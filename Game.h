#ifndef GUARD_GAME_H
#define GUARD_GAME_H

#include "StdAfx.h"
#include "VisibleObject.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "Button.h"
#include "Wave.h"
#include "Text.h"
#include "TextManager.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"

class Game
{
	public:
		Game();
		~Game();

		enum GameState { Uninitialized, MenuScreen, Playing, Exiting};
		enum PlayerState { HoldingTower, DoingNothing };

		void start();

		void handle_events();
		void update_wave();
		void update_turret();
		void update_game();
		void draw_game(sf::RenderWindow&);

		std::string createEnemy();
		std::string createTower(int);
		std::string createProjectile(Tower&, Enemy*);


		bool isExiting(){ return _isExiting; };

		//clocks
		sf::Clock* _gTime;
	private:

		bool _isExiting;

		//Individual objects
		VisibleObject* _map;
		VisibleObject* _ui;

		//Managers and controllers
		ObjectManager* _objectManager;
		ObjectManager* _buttonManager;

		ObjectManager* _enemyManager;
		ObjectManager* _towerManager;
		ObjectManager* _projectileManager;

		TextManager* _textManager;

		TextureManager* _textures;

		//Tower/Enemy count for naming key's.
		int _towerNr;
		int _enemyNr;
		int _projNr;

		//Wave
		Wave* _wave;

		//Window
		sf::RenderWindow _mainWindow;

		//States
		GameState _gameState;
		PlayerState _playerState;


		//Player targets
		Button* _targetButton;
		Tower* _holdingTower;

		//TODO make conf file reader for the path, depending on map chosen
		std::vector<sf::Vector2f> _path = { sf::Vector2f(-51, 480), sf::Vector2f(350, 480), sf::Vector2f(350, 180), sf::Vector2f(850, 180) };

};

#endif
