#ifndef GUARD_WAVE_H
#define GUARD_WAVE_H

#include "StdAfx.h"

class Wave
{
	public:
		Wave();
		~Wave();

		void start();
		int tic();
		void prepare_next_wave();
		void setNextSpawn(const int&);

		bool isOn() { return _isOn; };
		bool isSpawnReady();

	private:
		bool _isOn;
		bool _spawnReady;

		int _time;
		int _time_to_next_spawn;
};

#endif
