#ifndef GUARD_VISIBLE_OBJECTS_H
#define GUARD_VISIBLE_OBJECTS_H

#include "StdAfx.h"

class VisibleObject
{
	public:
		VisibleObject();
		~VisibleObject() {  };

		void load(sf::Texture);
		void load(sf::Texture, sf::IntRect);

		void draw(sf::RenderWindow&);
		virtual void update(sf::Time) { };
		virtual bool nextFrame(int speed) {  };

		bool inSprite(float x, float y);
		bool inSprite(float x1, float y1, float x2, float y2);
		bool inRadiusOf(float x, float y, float r);

		bool isLoaded() { return _isLoaded; };
		bool isAlive() { return _isAlive; };

		void setPosition(float x, float y);
		void setCenterPosition(float x, float y);
		void setTextureRect(const sf::IntRect&);

		sf::Vector2f getPosition();
		sf::Vector2f getCenterPosition();

		std::string getKey() { return _key; };

	protected:
		//Check if object should be removed or not
		bool _isAlive;

		sf::Sprite _sprite;
		//Object can find itself in objectmanagers
		std::string _key;

	private:
		bool _isLoaded;
		sf::Texture _texture;
};

#endif
