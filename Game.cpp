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
	_projectileManager = new ObjectManager();
	
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

	//set player stats
	_money = 1000;
	_strMoney = getStrMoney();
	_life = 100;
	_strLife = getStrLife();

	//Buttons creation start
	ButtonTower* jonesB = new ButtonTower(Button::Jones, 50);
	jonesB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 200, 200, 40));
	jonesB->setPosition(816, 340);
	_buttonManager->add("jonesB", jonesB);

	ButtonTower* krosB = new ButtonTower(Button::Kros, 75);
	krosB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 160, 200, 40));
	krosB->setPosition(816, 280);
	_buttonManager->add("krosB", krosB);

	ButtonTower* felixB = new ButtonTower(Button::Felix, 100);
	felixB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 120, 200, 40));
	felixB->setPosition(816, 220);
	_buttonManager->add("felixB", felixB);

	Button* startB = new Button(Button::Start);
	startB->load(_textures->getTexture("buttons.png"), sf::IntRect(0, 240, 180, 54));
	startB->setPosition(836, 701);
	_buttonManager->add("startB", startB);
	//Buttons creation end

	//Text creation start
	Text* timeInfo = new Text(_wave->_strTime, sf::Vector2f(950, 480));
	_textManager->add("time", timeInfo);

	Text* levelInfo = new Text(_wave->_strLevel, sf::Vector2f(950, 450));
	_textManager->add("level", levelInfo);


	Text* lifeInfo = new Text(_strLife, sf::Vector2f(620, 659));
	_textManager->add("life", lifeInfo);

	Text* moneyInfo = new Text(_strMoney, sf::Vector2f(620, 695));
	_textManager->add("money", moneyInfo);
	//Text creation end

	//Wave timer
	sf::Int32 waveTicReady = _gTime->getElapsedTime().asMilliseconds();

	//Game speed
	const int TPS = 200;
	const int SKIP_TICKS =  1000 / TPS;
	const int MAX_FRAME_SKIP = 5;

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

			if(_holdingTower != NULL){
				_holdingTower->placing(_mainWindow);
			}

			//tic should only occure each second( 1000 milliseconds)
			if(_gTime->getElapsedTime().asMilliseconds() > waveTicReady){
				update_wave();
				waveTicReady += 1000;
			}

			if(_wave->isSpawnRead()){
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

void Game::update_turret()
{
	for(auto iter = _towerManager->begin(); iter != _towerManager->end(); iter++){
		sf::Vector2f pos = iter->second->getPosition();
		VisibleObject* result = _enemyManager->inRadiusAll(pos.x, pos.y, ((Tower*)iter->second)->getRadius());
		if(result != NULL){
			//check that enemy isnt going to die before shot is fired
			if(((Enemy*)result)->getPreHealth() > 0){
				//check tower isnt in the progress of being placed
				if(((Tower*)iter->second)->isPlaced()){
					//check tower isnt already shooting/reloading
					if(!((Tower*)iter->second)->isFiring()){
						((Tower*)iter->second)->fire(_gTime->getElapsedTime());
						createProjectile(*((Tower*)iter->second), (Enemy*)result);
					}
				}
			}
			else{
				continue;
			}
		}
	}
}

void Game::update_game()
{
	_textManager->updateAll();
	_enemyManager->updateAll(_gTime->getElapsedTime());
	_towerManager->updateAll(_gTime->getElapsedTime());
	_projectileManager->updateAll(_gTime->getElapsedTime());

	update_turret();
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
						if(_targetButton->getAction() == Button::Start){
							_wave->start();
							_buttonManager->getObject("startB")->
								setTextureRect(sf::IntRect(0, 240+54, 179, 54));
							break;
						}
						else {
							if(_targetButton->getAction() != Button::Start){
								int cost = ((ButtonTower*)_targetButton)->getCost();
								if(_money >= cost) {
									_money -= cost;
									_strMoney = getStrMoney();

									string key = createTower((int)_targetButton->getAction());
									_holdingTower = (Tower*)_towerManager->getObject(key);
									_playerState = Game::HoldingTower;
								}
							}
						}
					}
					VisibleObject* result = _towerManager->inSpriteAll(event.mouseButton.x, event.mouseButton.y);
					if(result != NULL){
						_targetTower = (Tower*)result;
						_playerState = Targeting;
					}
				}
				break;
			}
			case Targeting :
			{
				if(event.type == sf::Event::KeyPressed){
					if(event.key.code == sf::Keyboard::Escape){
						_targetTower = NULL;
						_playerState = Game::DoingNothing;
						break;
					}
				}
				if(event.type == sf::Event::MouseButtonPressed){
					_targetTower = NULL;
					_playerState = Game::DoingNothing;
					break;
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
					Tower* result = (Tower*)_towerManager->inSpriteAll(event.mouseButton.x, event.mouseButton.y);
					if(result != NULL && result != _holdingTower){
						string key = upgradeTower(result, _holdingTower);
						Tower* tower = (Tower*)_towerManager->getObject(key);
						sf::Vector2f pos = result->getPosition();
						tower->place(pos.x, pos.y);
						_holdingTower = NULL;
						_playerState = Game::DoingNothing;
					}
					else{
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
			_projectileManager->drawAll(rw);

			draw_radius(rw);

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

void Game::draw_radius(sf::RenderWindow& rw)
{
	for(auto iter = _towerManager->begin(); iter != _towerManager->end(); iter++){
		if(iter->second != NULL){
			if(!((Tower*)iter->second)->isPlaced()
					|| ((Tower*)iter->second) == _targetTower)
			{
				sf::Vector2f pos = iter->second->getPosition();
				float r = ((Tower*)iter->second)->getRadius();
				sf::CircleShape rc(r);
				sf::Vector2f npos(pos.x - r, pos.y - r);
				rc.setPosition(npos);
				rc.setOutlineThickness(1);
				rc.setFillColor(sf::Color(0,0,0,0));
				rc.setOutlineColor(sf::Color(0,0,0));
				rw.draw(rc);
			}
		}
	}
}

string Game::createEnemy()
{
	const std::string key = "enemy" + to_string(_enemyNr);
	Enemy::EnemyType type = (Enemy::EnemyType) _wave->getEnemyType();

	Enemy* en = new Enemy(type, *_textures, key, _gTime->getElapsedTime());
	_enemyManager->add(key, en);
	en->setMovementPath(_path);
	en->setSpawnLocation();
	en->setCenterOrigin();

	//Set delay for next spawn
	_wave->setNextSpawn(en->getSpawnDelay());

	_enemyNr++;
	return key;
}

string Game::createTower(int i)
{
	const string key = "tower"+to_string(_towerNr++);
	Tower* tower = new Tower(i , *_textures, key);
	tower->setCenterOrigin();
	_towerManager->add(key, tower);
	return key;
}

string Game::upgradeTower(Tower* oldT, Tower* newT)
{
	int upgT = (oldT->getTypeInt()) * 10 + newT->getTypeInt();

	_towerManager->remove(oldT->getKey());
	_towerManager->remove(newT->getKey());

	return createTower(upgT);
}

string Game::createProjectile(Tower& T, Enemy* E)
{
	const string key = "projectile" + to_string(_projNr++);
	Projectile* pr = new Projectile(key, *_textures , T, E, _gTime->getElapsedTime());
	pr->setCenterOrigin();
	_projectileManager->add(key, pr);

	E->preDamage(pr->getDmg());
	return key;
}



int main()
{
	Game* game = new Game();
	game->start();
}
