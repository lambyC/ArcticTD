#ifndef GUARD_TEXT_MANAGER_H
#define GUARD_TEXT_MANAGER_H

#include "StdAfx.h"
#include "Text.h"

class TextManager
{

	public:
		TextManager();
		~TextManager();

		void add(std::string name, Text* object);
		void remove(std::string name);

		Text* getObject(std::string);

		void drawAll(sf::RenderWindow& rw);
		void updateAll();

		std::map<std::string, Text*>::iterator begin() { return _textMap.begin(); };
		std::map<std::string, Text*>::iterator end() { return _textMap.end(); };

	private:
		std::map<std::string, Text*> _textMap;

		struct Deallocator
		{
			void operator()(const std::pair<std::string, Text*>& p) const
			{
				delete p.second;
			}
		};

};






#endif
