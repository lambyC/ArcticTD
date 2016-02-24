#include "ObjectManager.h"

using namespace std;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	std::for_each(_objects.begin(), _objects.end(), Deallocator());
}

void ObjectManager::add(string key, VisibleObject* object)
{
	_objects.insert(pair<string, VisibleObject*>(key, object));
}

void ObjectManager::remove(std::string key)
{
	std::map<std::string, VisibleObject*>::iterator result = _objects.find(key);
	if(result != _objects.end()){
		delete result->second;
		_objects.erase(result);
	}
}

void ObjectManager::updateAll(sf::Time elapsedTime)
{
	std::map<std::string, VisibleObject*>::iterator iter = _objects.begin();
	while(iter != _objects.end()){
		if(iter->second->isAlive()){
			iter->second->update(elapsedTime);
			iter++;
		}
		else{
			remove(iter->first);
			return;
		}
	}
}

void ObjectManager::drawAll(sf::RenderWindow& rw)
{
	std::map<std::string, VisibleObject*>::iterator iter = _objects.begin();
	while(iter != _objects.end()){
		iter->second->draw(rw);
		iter++;
	}
}

VisibleObject* ObjectManager::inSpriteAll(float x, float y)
{
	std::map<std::string, VisibleObject*>::iterator iter = _objects.begin();
	while(iter != _objects.end()){
		if(iter->second->inSprite(x, y)){
			return iter->second;
		}
		iter++;
	}
	return NULL;
}

VisibleObject* ObjectManager::inSpriteAll(float x1, float y1, float x2, float y2)
{
	std::map<std::string, VisibleObject*>::iterator iter = _objects.begin();
	while(iter != _objects.end()){
		if(iter->second->inSprite(x1, y1, x2, y2)){
			return iter->second;
		}
		iter++;
	}
	return NULL;
}

VisibleObject* ObjectManager::inRadiusAll(float x1, float y1, float r)
{
	std::map<std::string, VisibleObject*>::iterator iter = _objects.begin();
	while(iter != _objects.end()){
		if((iter->second)->inRadiusOf(x1, y1, r)){
			return iter->second;
		}
		iter++;
	}
	return NULL;
}

int ObjectManager::getObjectCount()
{
	return _objects.size();
}

VisibleObject* ObjectManager::getObject(const string& key)
{
	map<string, VisibleObject*>::iterator result = _objects.find(key);
	if(result == _objects.end()){
		cout << key << endl;
		throw(key);
	}
	return result->second;
}
