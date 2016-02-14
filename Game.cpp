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
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Arctic TD", sf::Style::Titlebar );

	_objectManager = new ObjectManager();
	_buttonManager = new ObjectManager();

	_wave = new Wave();

	_textures = new TextureManager();
	_textures->loadAddAll("resources/textures/");

	//Objects to be drawn manually for priority reasons
	_map = new VisibleObject();
	_map->load(_textures->getTexture("arctic_map.png"));
	_ui = new VisibleObject();
	_ui->load(_textures->getTexture("arctic_map_ui.png"));

	_gTime = new sf::Clock();
	_gameState = Playing;

	//Buttons
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

	//Game speed
	const int TPS = 30;
	const int SKIP_TICKS =  1000 / TPS;
	const int MAX_FRAME_SKIP = 10;

	sf::Int32 next_game_tic = _gTime->getElapsedTime().asMilliseconds();
	int loops;

	while(!isExiting()){
		loops = 0;
		while(_gTime->getElapsedTime().asMilliseconds() > next_game_tic
				&& loops < MAX_FRAME_SKIP )
		{
		if(_gameState == Playing){

			handle_events();
			update_game();

			if(_wave->isOn()){
				_wave->tic();
				if(_wave->isSpawnReady()){
					//Spawn Eneemty
				}
			}
			else{
				_buttonManager->getObject("startB")->
					setTextureRect(sf::IntRect(0, 240, 179, 54));
			}
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

void Game::update_game()
{

}

void Game::handle_events()
{
	sf::Event event;
	while(_mainWindow.pollEvent(event)){

	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::M){
			_gameState = MenuScreen;
		}
		if(event.key.code == sf::Keyboard::Escape){
			_playerState = DoingNothing;
		}
	}
	switch(_playerState)
	{
		case DoingNothing :
		{
			if(event.type == sf::Event::MouseMoved){
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
			if(event.type == sf::Event::MouseButtonPressed){
				if(_targetButton != NULL){
					if(_targetButton->_action == Button::Start){
						_wave->start();
						_buttonManager->getObject("startB")->
							setTextureRect(sf::IntRect(0, 240+54, 179, 54));
					}
				}
			}
			break;
		}
		case HoldingTower :
		{
			break;
		}
	}
	}
};

void Game::draw_game(sf::RenderWindow& rw)
{
	switch(_gameState)
	{
		case Uninitialized : { break; }
		case Playing :
		{
			_map->draw(rw);

			_objectManager->drawAll(rw);

			_ui->draw(rw);

			_buttonManager->drawAll(rw);

			break;
		}
		case MenuScreen :
		{

		}
		case Exiting : { break; }
	}
};



int main()
{
	Game* game = new Game();
	game->start();
}
