#ifndef GUARD_VISIBLE_OBJECTS_H
#define GUARD_VISIBLE_OBJECTS_H

#include "StdAfx.h"

class VisibleObject
{
	public:
		VisibleObject();
		virtual ~VisibleObject();

		void load(sf::Texture);
		void load(sf::Texture, sf::IntRect);

		void draw(sf::RenderWindow&);
		virtual void update();

		bool inSprite(float x, float y);
		bool inSprite(float x1, float y1, float x2, float y2);
		bool inRadiusOf(float x, float y, float r);
		bool isLoaded(){ return _isLoaded;}

		void setPosition(float x, float y);
		void setCenterPosition(float x, float y);
		void setTextureRect(const sf::IntRect&);

		sf::Vector2f getPosition();
		sf::Vector2f getCenterPosition();

	protected:
		sf::Sprite _sprite;
		std::string _key;

	private:
		bool _isLoaded;
		sf::Texture _texture;
};

#endif
