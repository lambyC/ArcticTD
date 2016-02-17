#ifndef GUARD_OBJECT_MANAGER_H
#define GUARD_OBJECT_MANAGER_H

#include "StdAfx.h"
#include "VisibleObject.h"

class ObjectManager
{
	public:
		ObjectManager();
		~ObjectManager();

		void add(std::string key, VisibleObject* object);
		void remove(std::string);

		void updateAll(sf::Time);
		void drawAll(sf::RenderWindow&);

		VisibleObject* inSpriteAll(float x, float y);
		VisibleObject* inSpriteAll(float x1, float y1, float x2, float y2);
		VisibleObject* inRadiusAll(float x, float y, float r);

		int getObjectCount();
		VisibleObject* getObject(const std::string&);

	private:
		std::map<std::string, VisibleObject*> _objects;

		struct Deallocator
		{
			void operator()(const std::pair<std::string, VisibleObject*>& p) const
			{
				delete p.second;
			}
		};
};

#endif
