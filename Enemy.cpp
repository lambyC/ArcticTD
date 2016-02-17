#include "Enemy.h"

using namespace std;

Enemy::Enemy(EnemyType type, TextureManager& textures,const string& key, sf::Time time)
	:_point(1),
	_isAlive(true),
	_maxFrames(2),
	_isRight(false),
	_type(type),
	_key(key)
{
	loadEnemyStatsFromFile(type);
	loadEnemyTextureFromFile(textures);

	_size = sf::IntRect(0,0,50,50);
	_frame = sf::IntRect(0,0,50,50);

	_sprite.setTextureRect(_size);

	_moveTime = time.asMilliseconds();
	_frameTime = time.asMilliseconds();
}

Enemy::~Enemy()
{

}

void Enemy::update(sf::Time elapsedTime)
{
	if(elapsedTime.asMilliseconds() > _moveTime){
		move();
		_moveTime += 10;
	}
	//update _sprite
	//Move animation forward
	if(elapsedTime.asMilliseconds() > _frameTime){
		//Check if at either end of Animation
		if(_frame.left == _size.width * _maxFrames || _frame.left == 0)
			_isRight = _isRight ? false : true;
		//move frame according to direction
		_frame.left += _isRight ? _size.width : - _size.width;
		//Check direction
		_frame.top = _size.height * (int)_direction;
		//update
		_sprite.setTextureRect(_frame);
		//Add time
		_frameTime += 100;
	}

	//TODO mke more red the more dmg'd the enemy is
	/*
	int procent = _health / _initialHp;
	_sprite.setColor(sf::Color(255, 255 * procent, 255 * procent));
	*/
}

void Enemy::move()
{
	//TODO Make enemies able to move in all direction not just bottom/left to top/right
	//difference between point and current position
	sf::Vector2f cpos = getPosition();
	float dx = _path[_point].x - cpos.x;
	float dy = _path[_point].y - cpos.y;
	//Get fastest way to the point
	float hyp = std::sqrt(std::pow(dx,2) + std::pow(dy,2));
	//if at point move to next point
	if(dx ==  0 && dy == 0){
		//if at last point kill enemy, + 1 since size() max value
		if(_point + 1 == (int)_path.size())
			kill();
		else
			_point++;
		//no point moving since we wouldnt go anywhere
		return;
	}
	//give enemy its new coordinates
	float nx = cpos.x + 1 * (dx/hyp);
	float ny = cpos.y + 1 * (dy/hyp);

	setPosition(nx, ny);

	//check direction,
	if(abs(dx) > abs(dy))
		_direction = Right;
	else
		_direction = Up;
}

void Enemy::kill()
{

}

void Enemy::loadEnemyStatsFromFile(const EnemyType& type)
{
	ifstream inFile("resources/config/EnemyStatsConfig.txt");
	string line;
	//vector of all stats, so to loop through them each
	vector<int> statsVect = {_health, _speed, _spawnDelay};
	vector<int>::size_type vec_i = 0;
	while(getline(inFile, line)){
		istringstream isline(line);
		string::size_type mid = line.find("=");
		if(line.substr(0, mid) == to_string(type)){
			//everything past the "=" sign
			string data = line.substr(mid + 1, line.size());
			typedef string::iterator iter;
			iter i = data.begin();
			while(i != data.end()){
				i = find_if_not(i, data.end(), isComma);
				iter j = find_if(i , data.end(), isComma);
				if(i != data.end() && vec_i != 3){
					statsVect[vec_i] = atoi(string(i, j).c_str());
					i = j;
				}
			}
			inFile.close();
			inFile.clear();
			_initialHealth = _health;
			return;
		}
	}
}

void Enemy::loadEnemyTextureFromFile(TextureManager& textures)
{
	ifstream inFile("resources/config/TextureForEnemiesConfig.txt");
	string line;
	string path;
	int type = (int)_type;
	while(getline(inFile, line)){
		istringstream isline(line);
		string::size_type mid = line.find("=");
		if(line.substr(0, mid) == to_string(type)){
			load(textures.getTexture(line.substr(mid + 1, line.size())));
			inFile.close();
			inFile.clear();
			break;
		}
	}
}

void Enemy::setSpawnLocation()
{
	sf::Vector2f pos = _path[0];
	_sprite.setPosition(pos.x, pos.y);
}
