#include "MenuScreen.h"

MenuScreen::MenuScreen(TextureManager* textures)
{
	_textures = textures;
}

MenuScreen::~MenuScreen()
{
}

MenuScreen::MenuResult MenuScreen::show_choose(sf::RenderWindow& rw)
{
	VisibleObject* background = new VisibleObject();
	background->load(_textures->getTexture("background.png"));

	MenuScreenObject* title = new MenuScreenObject(_textures->getTexture("menu_text.png")
												 , sf::IntRect(0, 0, 611, 236));
	title->setPosition(207, 184);
	_menuObjects.add("title", title);

	MenuScreenObject* sub_title =new MenuScreenObject(_textures->getTexture("menu_text.png")
														, sf::IntRect(0, 236, 559, 46));
	sub_title->setPosition(396, 416);
	_menuObjects.add("sub_title", sub_title);

	MenuScreenObject* start_continue = new MenuScreenObject(_textures->getTexture("menu_text.png"), sf::IntRect(0, 300, 120, 33));
	start_continue->setPosition(450, 550);
	start_continue->_action = MenuScreen::Play;
	_menuObjects.add("start_continue", start_continue);

	MenuScreenObject* options = new MenuScreenObject(_textures->getTexture("menu_text.png"), sf::IntRect(0, 353, 170, 43));
	options->setPosition(430, 600);
	options->_action = MenuScreen::Options;
	_menuObjects.add("options", options);

	MenuScreenObject* exit = new MenuScreenObject(_textures->getTexture("menu_text.png"), sf::IntRect(0, 410, 140, 53));
	exit->setPosition(460, 650);
	exit->_action = MenuScreen::Exit;
	_menuObjects.add("exit", exit);

	MenuScreenObject* target = NULL;

	while(rw.isOpen()){
		sf::Event event;
		while(rw.pollEvent(event)){
			if(event.type == sf::Event::MouseMoved){
				//If mouse no longer over target reset color
				if(target != NULL)
					if(target->inSprite(event.mouseMove.x, event.mouseMove.y) == false)
						target->changeColour(sf::Color(255, 255, 255));
				VisibleObject* result = _menuObjects.inSpriteAll(event.mouseMove.x, event.mouseMove.y);
				if(result != NULL){
					target = (MenuScreenObject*) result;
					target->changeColour(sf::Color(120, 0 ,50));
				}
			}
			if(event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == sf::Mouse::Left){
					VisibleObject* result = _menuObjects.inSpriteAll(event.mouseButton.x, event.mouseButton.y);
					if(result != NULL){
						MenuScreenObject* r = (MenuScreenObject*) result;
						return (*r)._action;
						std::cout << (*r)._action << std::endl;
					}
				}
			}
		}
		rw.clear();

		background->draw(rw);
		_menuObjects.drawAll(rw);

		rw.display();
	}
	return MenuScreen::Nothing;
}

MenuScreen::MenuScreenObject::MenuScreenObject(sf::Texture texture, sf::IntRect rect)
{
	load(texture);
	setTextureRect(rect);
}

MenuScreen::MenuScreenObject::~MenuScreenObject()
{
}

void MenuScreen::MenuScreenObject::update(sf::Time)
{

}

void MenuScreen::MenuScreenObject::changeColour(sf::Color color)
{
	_sprite.setColor(color);
}

bool MenuScreen::MenuScreenObject::isAnimationComplete()
{
	if(_isAnimationComplete)
		return true;
	return false;
}
