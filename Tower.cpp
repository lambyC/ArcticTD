#include "Tower.h"

using namespace std;

Tower::Tower(int type, TextureManager& textures, string key)
	:
	_isPlaced(false),
	_isFiring(false),
	_tState(Waiting),
	_type((TowerType)type),
	_shotNr(0)
{
	_key = key;
	_isAlive = true;

	loadFromBaseType(textures);
	setStatsFromType(type);

	
	_size = sf::IntRect(0, 0, 64, 64);
	_frame = sf::IntRect(0, 0, 64, 64);
	
	_sprite.setTextureRect(_size);


	_frameRow = First;
	_isRight = false;
}

void Tower::update(sf::Time elapsedTime)
{
	switch(_tState)
	{
		case Building :
		{
			break;
		}
		case Waiting :
		{
			if(isFiring()){
				if(elapsedTime.asMilliseconds() > _fireTime){
					_isFiring = false;
					_shotNr++;
				}
			}
			break;
		}
		case Firing :
		{
			if(isFiring()){
				if(elapsedTime.asMilliseconds() > getFrameTime()){
					if(nextFrame(_fireRate / _maxFrames)){
						setTextureRect(_size);
						_tState = Waiting;
					}
				}
			}
			break;
		}
		case Upgrading :
		{
			break;
		}
	}
}

void Tower::placing(sf::RenderWindow& rw){
	if(!isPlaced()){
		sf::Vector2i mousePos = sf::Mouse::getPosition(rw);
		_sprite.setPosition(mousePos.x, mousePos.y);
		return;
	}
}

void Tower::fire(sf::Time elapsedTime)
{
	_isFiring = true;
	_tState = Firing;
	_fireTime = elapsedTime.asMilliseconds() + _fireRate;
	setFrameTime(elapsedTime.asMilliseconds());
}

void Tower::loadFromBaseType(TextureManager& textures)
{
	std::ifstream inFile("resources/config/TextureForTowersConfig.txt");
	std::string line;
	std::string path;
	int type = (int)_type;
	while(std::getline(inFile, line)){
		std::istringstream isline(line);
		std::string::size_type mid = line.find("=");
		if(line.substr(0, mid) == std::to_string(type)){
			load(textures.getTexture(line.substr(mid + 1, line.size())));
			inFile.close();
			inFile.clear();
			break;
		}
	}
}

void Tower::setStatsFromType(int type)
{
	std::ifstream inFile("resources/config/TowerStatsConfig.txt");
	string line;
	//vector of all stats, so to loop through them each
	int stats[4];
	int ar_i = 0;
	while(getline(inFile, line)){
		istringstream isline(line);
		string::size_type mid = line.find("=");
		if(mid == line.size())
			continue;
		if(line.substr(0, mid) == to_string(type)){
			//everything past the "=" sign
			string data = line.substr(mid + 1, line.size());
			typedef string::iterator iter;
			iter i = data.begin();
			while(i != data.end()){
				i = find_if_not(i, data.end(), isComma);
				iter j = find_if(i , data.end(), isComma);
				if(i != data.end() && ar_i != 4){
					stats[ar_i++] = atoi(string(i, j).c_str());
					i = j;
				}
			}
			
			_dmg = stats[0];
			_fireRate = stats[1];
			_radius = stats[2];
			_maxFrames = stats[3];

			inFile.close();
			inFile.clear();
			return;
		}
	}
}

Tower::TowerType Tower::getNewTowerType(TowerType base, TowerType upg)
{
	return (TowerType)((base * 10) + upg);
}


