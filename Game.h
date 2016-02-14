#ifndef GUARD_GAME_H
#define GUARD_GAME_H

#include "StdAfx.h"
#include "VisibleObject.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "Button.h"
#include "Wave.h"

class Game
{
	public:
		Game();
		~Game();

		enum GameState { Uninitialized, MenuScreen, Playing, Exiting};
		enum PlayerState { HoldingTower, DoingNothing };

		void start();
		void handle_events();
		void update_game();
		void draw_game(sf::RenderWindow&);

		bool isExiting(){ return _isExiting; };

	private:

		bool _isExiting;

		VisibleObject* _map;
		VisibleObject* _ui;

		//Controling the flow of the game
		ObjectManager* _objectManager;
		ObjectManager* _buttonManager;

		TextureManager* _textures;

		Wave* _wave;

		sf::RenderWindow _mainWindow;

		//States
		GameState _gameState;
		PlayerState _playerState;

		//clocks
		sf::Clock* _gTime;

		//Player targets
		Button* _targetButton;

};

#endif
