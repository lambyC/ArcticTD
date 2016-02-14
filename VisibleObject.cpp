#include "VisibleObject.h"

using std::sqrt; using std::pow;


VisibleObject::VisibleObject()
{

}

VisibleObject::~VisibleObject()
{

}

void VisibleObject::load(sf::Texture texture)
{
	_texture = texture;
	_sprite.setTexture(_texture);
	_isLoaded = true;
}

void VisibleObject::load(sf::Texture texture, sf::IntRect intRect)
{
	load(texture);
	_sprite.setTextureRect(intRect);
}

void VisibleObject::draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
}

void VisibleObject::update()
{
}

bool VisibleObject::inSprite(float x, float y)
{
	sf::Vector2f pos = _sprite.getPosition();
	sf::IntRect bound = _sprite.getTextureRect();
	if(pos.x <= x && pos.y <= y
	&& (pos.x + bound.width) >= x
	&& (pos.y + bound.height) >= y)
	{
		return true;
	}
	return false;
}

bool VisibleObject::inSprite(float x1, float y1, float x2, float y2)
{
	if(inSprite(x1, y1) && inSprite(x2, y2))
		return true;
	return false;
}

bool VisibleObject::inRadiusOf(float x, float y, float r)
{
	if(sqrt(pow(x,2) + pow(y,2)) <= r)
		return true;
	return false;
}

void VisibleObject::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

void VisibleObject::setCenterPosition(float x, float y)
{
	sf::IntRect bound = _sprite.getTextureRect();
	_sprite.setPosition(x - (bound.width / 2), y - (bound.height / 2));
}

void VisibleObject::setTextureRect(const sf::IntRect& intRect){
	_sprite.setTextureRect(intRect);
}

sf::Vector2f VisibleObject::getPosition()
{
	return _sprite.getPosition();
}

sf::Vector2f VisibleObject::getCenterPosition()
{
	sf::IntRect rec = _sprite.getTextureRect();
	sf::Vector2f pos = _sprite.getPosition();
	sf::Vector2f ret(pos.x + (rec.width/2), pos.y + (rec.height/2));
	return ret;
}

