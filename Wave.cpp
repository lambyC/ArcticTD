#include "Wave.h"

Wave::Wave()
	:_isOn(false),
	_time(60),
	_time_to_next_spawn(0),
	_level(0)
{
	_strLevel = getLevelstr();
	_strTime = getTimestr();
}

Wave::~Wave()
{

}

void Wave::start()
{
	_isOn = true;
}

void Wave::stop()
{
	_isOn = false;
}

void Wave::prepare_next_wave()
{
	_time = 60;

	_level += 1;
	_strLevel = getLevelstr();
}

void Wave::setNextSpawn(const int& i)
{
	_time_to_next_spawn += i;
}

int Wave::tic()
{
	_time -= 1;
	//update info
	_strTime = getTimestr();
	return _time;
}

bool Wave::isSpawnReady()
{
	if((60 - _time) > _time_to_next_spawn)
		return true;
	return false;
}

std::string Wave::getTimestr()
{
	return std::to_string(_time);
}

std::string Wave::getLevelstr()
{
	return std::to_string(_level);
}

