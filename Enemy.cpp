#include "Enemy.h"

using namespace std;

Enemy::Enemy(EnemyType type, TextureManager& textures,const string& key, sf::Time time)
	:_point(1),
	_eState(Alive),
	_type(type)
{
	_key = key;
	_isAlive = true;
	_maxFrames = 2;
	_isRight = false;

	loadEnemyStatsFromFile(type);
	loadEnemyTextureFromFile(textures);

	if((int)type % 5 == 0 && (int)type != 0){
		_size = sf::IntRect(0,0,80,80);
		_frame = sf::IntRect(0,0,80,80);
	}
	else{
		_size = sf::IntRect(0,0,50,50);
		_frame = sf::IntRect(0,0,50,50);
	}

	_sprite.setTextureRect(_size);

	_moveTime = time.asMilliseconds();

	setFrameTime(time.asMilliseconds());
}

Enemy::~Enemy()
{

}

void Enemy::update(sf::Time elapsedTime)
{
	switch(_eState)
	{
		case Alive :
			{
				if(elapsedTime.asMilliseconds() > _moveTime){
					move();
					_moveTime += 40;
				}
				if(elapsedTime.asMilliseconds() > getFrameTime()){
					nextFrame(_speed * 10);
				}
				if(_health <= 0){
					_isAlive = false;
				}
				//make more red the more dmg'd the enemy is
				float procent = _health / _initialHealth;
				float c = 255 * procent;

				_sprite.setColor(sf::Color(255, c, c));

				break;
			}
		case Action :
			{

				break;
			}
		case Dying :
			{
				if(elapsedTime.asMilliseconds() > getFrameTime()){
					nextFrame(_speed * 10);
				}
				break;
			}
	}

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
	if(abs(dx) < 2 && abs(dy) < 2){
		//if at last point kill enemy, + 1 since size() max value
		if(_point + 1 == (int)_path.size())
			kill();
		else
			_point++;
		//no point moving since we wouldnt go anywhere
		return;
	}
	//give enemy its new coordinates
	float nx = cpos.x + 2 * (1 * (dx/hyp));
	float ny = cpos.y + 2 * (1 * (dy/hyp));

	setPosition(nx, ny);

	//check direction,
	if(abs(dx) > abs(dy))
		_frameRow = First;
	else
		_frameRow = Second;
}

void Enemy::kill()
{
	_isAlive = false;
}

void Enemy::loadEnemyStatsFromFile(const EnemyType& type)
{
	ifstream inFile("resources/config/EnemyStatsConfig.txt");
	string line;
	//vector of all stats, so to loop through them each
	int stats[3];
	int ar_i = 0;
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
				if(i != data.end() && ar_i != 3){
					stats[ar_i++] = atoi(string(i, j).c_str());
					i = j;
				}
			}
			
			_health = stats[0];
			_initialHealth = stats[0];
			_preHealth = stats[0];
			_speed = stats[1];
			_spawnDelay = stats[2];

			inFile.close();
			inFile.clear();
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

void Enemy::damage(int dmg)
{
	_health -= dmg;
}

void Enemy::preDamage(int dmg)
{
	_preHealth -= dmg;
}

void Enemy::setSpawnLocation()
{
	sf::Vector2f pos = _path[0];
	_sprite.setPosition(pos.x, pos.y);
}
