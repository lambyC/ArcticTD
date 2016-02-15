#include "TextManager.h"

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	std::for_each(_textMap.begin(), _textMap.end(), Deallocator());
}


void TextManager::remove(std::string name)
{
	std::map<std::string, Text*>::iterator result =  _textMap.find(name);
	if(result != _textMap.end()){
		delete result->second;
		_textMap.erase(result);
	}
}

void TextManager::add(std::string name, Text* object)
{
	_textMap.insert(std::pair<std::string, Text*>(name, object));
}

Text* TextManager::getObject(std::string name)
{
	std::map<std::string, Text*>::iterator result =  _textMap.find(name);
	if(result != _textMap.end()){
		return result->second;
	}
	return NULL;
}

void TextManager::drawAll(sf::RenderWindow& rw)
{
	std::map<std::string, Text*>::iterator iter = _textMap.begin();
	while(iter != _textMap.end()){
		iter->second->draw(rw);
		iter++;
	}
}

void TextManager::updateAll()
{
	std::map<std::string, Text*>::iterator iter = _textMap.begin();
	while(iter != _textMap.end()){
		iter->second->update();
		iter++;
	}
}


