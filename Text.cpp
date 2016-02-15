#include "Text.h"


Text::Text()
{

}

Text::Text(std::string& str, sf::Vector2f pos)
	:_str(&str)
{
	loadFont();
	_text.setFont(_font);
	_text.setString(*_str);
	_text.setPosition(pos);
	_text.setCharacterSize(12);
	_text.setColor(sf::Color(225,23,23));
}

Text::~Text()
{
	delete _str;
	_str = NULL;
}

void Text::update()
{
	_text.setString(*_str);
}

void Text::draw(sf::RenderWindow& rw)
{
	rw.draw(_text);
}

void Text::setPosition(sf::Vector2f pos)
{
	_text.setPosition(pos);
}

void Text::loadFont()
{
	_font.loadFromFile("resources/fonts/DejaVuSans-Bold.ttf");
}
