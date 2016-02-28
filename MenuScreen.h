#ifndef GUARD_MENU_SCREEN_H
#define GUARD_MENU_SCREEN_H

#include "StdAfx.h"
#include "VisibleObject.h"
#include "ObjectManager.h"
#include "TextureManager.h"

class MenuScreen
{
	public:
		MenuScreen(TextureManager*);
		~MenuScreen();

		enum MenuResult {Nothing, Play, Options, Exit};

		MenuResult show_choose(sf::RenderWindow& rw);
	private:

		class MenuScreenObject : public VisibleObject
		{
			public:
				MenuScreenObject();
				MenuScreenObject(sf::Texture, sf::IntRect rect);
				~MenuScreenObject();

				void update(sf::Time);
				void changeColour(sf::Color);
				bool isAnimationComplete();

				MenuResult _action;
			private:
				bool _isAnimationComplete;

		};


		TextureManager* _textures;
		ObjectManager _menuObjects;
};

#endif
