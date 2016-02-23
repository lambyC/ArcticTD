#include "Projectile.h"

using namespace std;

Projectile::Projectile(string key, TextureManager& textures, Tower& tower , Enemy* enemy, sf::Time time)
	:
	_pState(Traveling),
	_dmg(tower.getDmg()),
	_speed(10),
	_target(enemy)
{
	_key = key;
	_isAlive = true;
	_maxFrames = 3;
	_isRight = false;
	_frameRow = First;

	load(textures.getTexture("red_bullet.png"));

	
	_size = sf::IntRect(0,0,16,16);
	_frame = sf::IntRect(0,0,16,16);

	_movementTime = time.asMilliseconds();
	setFrameTime(time.asMilliseconds());

	sf::Vector2f Tpos = tower.getPosition();
	setPosition(Tpos.x + 32, Tpos.y + 32);
	setTextureRect(_size);
}

Projectile::~Projectile()
{
}

void Projectile::update(sf::Time elapsedTime)
{
	switch(_pState)
	{
		case Charging :
			{
				break;
			}
		case Traveling :
			{
				if(elapsedTime.asMilliseconds() > _movementTime){
					move();
					_movementTime += 1;
				}
				if(elapsedTime.asMilliseconds() > getFrameTime()){
					nextFrame(_speed);
				}
				break;
			}
		case Exploding :
			{
				if(elapsedTime.asMilliseconds() > _frameTime){
					if(nextFrame(_speed)){
						_isAlive = false;
					}
				}
				break;
			}
		case NonExisting :
			{
				break;
			}
	}
}

void Projectile::move()
{
	sf::Vector2f pos = _sprite.getPosition();
	float dx = _target->getPosition().x - pos.x;
	float dy = _target->getPosition().y - pos.y;
	float hyp = sqrt(pow(dx, 2) + pow(dy, 2));

	if(abs(dx) < 1 && abs(dy) < 1){
		_frameRow = Second;
		_pState = Exploding;
		return;
	}

	float nx = pos.x + (1 * (dx/hyp));
	float ny = pos.y + (1 * (dy/hyp));
	_sprite.setPosition(nx, ny);
}

void Projectile::explode()
{


}
