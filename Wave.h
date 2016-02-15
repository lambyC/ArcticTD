#ifndef GUARD_WAVE_H
#define GUARD_WAVE_H

#include "StdAfx.h"

class Wave
{
	public:
		Wave();
		~Wave();

		int tic();

		void start();
		void stop();
		void prepare_next_wave();
		void setNextSpawn(const int&);

		bool isOn() { return _isOn; };
		bool isSpawnReady();

		int getTime() { return _time; };

		//get Info for game
		std::string getTimestr();
		std::string getLevelstr();

		//store string variation publicly so can be accessed by Game;
		std::string _strTime;
		std::string _strLevel;

	private:
		bool _isOn;
		bool _spawnReady;

		int _time;
		int _time_to_next_spawn;

		int _level;
};

#endif
