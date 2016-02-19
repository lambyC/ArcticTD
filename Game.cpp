#include "Game.h"

using namespace std;

Game::Game()
	:_gameState(Uninitialized),
	_playerState(DoingNothing),
	_targetButton(NULL)
{

}

void Game::start()
{
	//game is not already running
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Arctic TD", sf::Style::Titlebar );

	//managers
	_objectManager = new ObjectManager();
	_buttonManager = new ObjectManager();
	
	_enemyManager = new ObjectManager();
	_towerManager = new ObjectManager();
	
	_textManager = new TextManager();

	_wave = new Wave();

	//load all textures in texture director so they can quickly be accessed.
	//TODO: loads all images, extra skin packs will be loaded aswell, not optimal
	_textures = new TextureManager();
	_textures->loadAddAll("resources/textures/");

	//Objects to be drawn manually for priority reasons
	_map = new VisibleObject();
	_map->load(_textures->getTexture("arctic_map.png"));
	_ui = new VisibleObject();
	_ui->load(_textures->getTexture("arctic_map_ui.png"));

	_gTime = new sf::Clock();
	_gameState = Playing;

	//Buttons creation start
	Button* jonesB = new Button(Button::Jones);
	jonesB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 200, 200, 40));
	jonesB->setCenterPosition(916, 360);
	_buttonManager->add("jonesB", jonesB);

	Button* krosB = new Button(Button::Kros);
	krosB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 160, 200, 40));
	krosB->setCenterPosition(916, 300);
	_buttonManager->add("krosB", krosB);

	Button* felixB = new Button(Button::Felix);
	felixB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 120, 200, 40));
	felixB->setCenterPosition(916, 240);
	_buttonManager->add("felixB", felixB);

	Button* startB = new Button(Button::Start);
	startB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 240, 170, 54));
	startB->setCenterPosition(924, 727);
	_buttonManager->add("startB", startB);
	//Buttons creation end

	//Text creation start
	Text* timeInfo = new Text(_wave->_strTime, sf::Vector2f(950, 480));
	_textManager->add("time", timeInfo);

	Text* levelInfo = new Text(_wave->_strLevel, sf::Vector2f(950, 450));
	_textManager->add("level", levelInfo);
	//Text creation end

	//Wave timer
	sf::Int32 waveTicReady = _gTime->getElapsedTime().asMilliseconds();

	//Game speed
	const int TPS = 100;
	const int SKIP_TICKS =  1000 / TPS;
	const int MAX_FRAME_SKIP = 10;

	sf::Int32 next_game_tic = _gTime->getElapsedTime().asMilliseconds();
	int loops;

	//Game heart beat
	while(!isExiting()){
		loops = 0;
		while(_gTime->getElapsedTime().asMilliseconds() > next_game_tic
				&& loops < MAX_FRAME_SKIP )
		{
		//Pause game if not in playing state
		if(_gameState == Playing){


			handle_events();

			//tic should only occure each second( 1000 milliseconds)
			if(_gTime->getElapsedTime().asMilliseconds() > waveTicReady){
				update_wave();
				waveTicReady += 1000;
			}

			if(_wave->isSpawnRead()){
					cout << "spawn"<< _wave->getSpawnNr() << endl;
					createEnemy();
			}

			update_game();

		}
		next_game_tic += SKIP_TICKS;
		loops++;
	}
		_mainWindow.clear();

		draw_game(_mainWindow);

		_mainWindow.display();
	}
	_mainWindow.close();
}

void Game::update_wave()
{
	//Game controls most of the wave flow, as to make it easier to handle events in order.
	if(_wave->isOn()){
		_wave->tic();
		if(_wave->getTime() <= 0){
			_buttonManager->getObject("startB")->
				setTextureRect(sf::IntRect(0, 240, 179, 54));
			_wave->stop();
		}
	}

}

void Game::update_game()
{
	_textManager->updateAll();
	_enemyManager->updateAll(_gTime->getElapsedTime());
	_towerManager->updateAll(_gTime->getElapsedTime());
}

void Game::handle_events()
{
	sf::Event event;
	while(_mainWindow.pollEvent(event)){

	//event handling irrespective of _playerState
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::M){
			_gameState = MenuScreen;
		}
	}
	switch(_playerState)
	{
		case DoingNothing :
		{
			if(event.type == sf::Event::MouseMoved){
				//Check if button has mouse hovering over it
				//change colour if true, change back if not
				if(_targetButton != NULL){
					if(_targetButton->inSprite(event.mouseMove.x, event.mouseMove.y) == false)
						_targetButton->changeColour(sf::Color(255, 255, 255));
				}
				VisibleObject* result = _buttonManager->inSpriteAll(event.mouseMove.x, event.mouseMove.y);
				if(result != NULL){
					_targetButton = (Button*) result;
					_targetButton->changeColour(sf::Color(20, 255, 255));
				}
				else{
					_targetButton = NULL;
				}
			}
			//Buttons pressed
			if(event.type == sf::Event::MouseButtonPressed){
				if(_targetButton != NULL){
					if(_targetButton->_action == Button::Start){
						_wave->start();
						_buttonManager->getObject("startB")->
							setTextureRect(sf::IntRect(0, 240+54, 179, 54));
					}
					else {
						if(_targetButton->_action != Button::Start){
							string key = createTower((int)_targetButton->_action);
							_holdingTower = (Tower*)_towerManager->getObject(key);
							_playerState = Game::HoldingTower;
						}

					}
				}
			}
			break;
		}
		case HoldingTower :
		{
			if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Escape){
					_towerManager->remove(_holdingTower->getKey());
					_holdingTower = NULL;
					_playerState = Game::DoingNothing;
					break;
				}
			}
			if(event.type == sf::Event::MouseButtonPressed){
				if(_map->inSprite(event.mouseButton.x, event.mouseButton.y)){
					_holdingTower->place();
					_holdingTower = NULL;
					_targetButton->changeColour(sf::Color(255,255,255));
					_playerState = Game::DoingNothing;
				}
			}
		}
		break;
		}
	}
};

void Game::draw_game(sf::RenderWindow& rw)
{
	//Draw the correct screen
	switch(_gameState)
	{
		case Uninitialized : { break; }
		case Playing :
		{
			_map->draw(rw);

			_objectManager->drawAll(rw);
			_enemyManager->drawAll(rw);
			_towerManager->drawAll(rw);

			_ui->draw(rw);

			_buttonManager->drawAll(rw);
			_textManager->drawAll(rw);

			break;
		}
		case MenuScreen :
		{

		}
		case Exiting : { break; }
	}
};

void Game::createEnemy()
{
	const std::string key = to_string(_enemyNr);
	Enemy::EnemyType type = (Enemy::EnemyType) _wave->getEnemyType();

	Enemy* en = new Enemy(type, *_textures, key, _gTime->getElapsedTime());
	_enemyManager->add(key, en);
	en->setMovementPath(_path);
	en->setSpawnLocation();

	//Set delay for next spawn
	_wave->setNextSpawn(en->getSpawnDelay());

	_enemyNr++;
}

std::string Game::createTower(int i)
{
	const string key = "tower"+to_string(_towerNr++);
	cout << key << endl;
	Tower* tower = new Tower(i , *_textures, key);
	_towerManager->add(key, tower);

	return key;
}

int main()
{
	Game* game = new Game();
	game->start();
}
