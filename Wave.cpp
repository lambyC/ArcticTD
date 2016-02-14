#include "Wave.h"

Wave::Wave()
	:_time(60),
	_time_to_next_spawn(0)
{

}

Wave::~Wave()
{

}

void Wave::start()
{
	_isOn = true;
}

void Wave::prepare_next_wave()
{
	_time = 60;
}

void Wave::setNextSpawn(const int& i)
{
	_time_to_next_spawn += i;
}

int Wave::tic()
{
	_time -= 1;
	if(_time == 0){
		_isOn = false;
		prepare_next_wave();
	}
	return _time;
}

bool Wave::isSpawnReady()
{
	if((60 - _time) > _time_to_next_spawn)
		return true;
	return false;
}
