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
		bool isSpawnRead();

		int getTime() { return _time; };
		int getTimeToNextSpawn() { return _timeToNextSpawn; };
		int getEnemyType() { return _waveSpawnVec[_spawnNr]; };
		int getSpawnNr() { return _spawnNr; };

		std::vector<int> loadWaveSpawnVec(const int&);

		//get Info for game
		std::string getTimestr();
		std::string getLevelstr();

		//store string variation publicly so can be accessed by Game;
		std::string _strTime;
		std::string _strLevel;

	private:
		bool _isOn;

		int _time;
		int _timeToNextSpawn;

		int _level;
		//holds all the enemy types to be spawned in order
		std::vector<int> _waveSpawnVec;
		int _spawnNr;

};

#endif
