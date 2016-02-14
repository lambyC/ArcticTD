#include "Button.h"

Button::Button()
{
}

Button::Button(ButtonType type)
	:_action(type)
{
}

Button::~Button()
{
}

void Button::setButtonType(ButtonType type)
{
	_action = type;
}

void Button::changeColour(sf::Color color)
{
	_sprite.setColor(color);
}
