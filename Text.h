#ifndef GUARD_TEXT_OBJECT_H
#define GUARD_TEXT_OBJECT_H

#include "StdAfx.h"

class Text
{

	public:
		Text();
		Text(std::string& str, sf::Vector2f);
		~Text();


		void update();
		void draw(sf::RenderWindow& rw);

		void loadFont();
		void setPosition(sf::Vector2f);

	private:

		std::string* _str;
		sf::Text _text;
		sf::Font _font;

};

#endif
