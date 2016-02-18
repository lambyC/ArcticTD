#include "Wave.h"

using namespace std;

Wave::Wave()
	:_isOn(false),
	_time(60),
	_timeToNextSpawn(5),
	_level(0),
	_spawnNr(0)
{
	_strLevel = getLevelstr();
	_strTime = getTimestr();
	_waveSpawnVec = loadWaveSpawnVec(_level);
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
	prepare_next_wave();
}

void Wave::prepare_next_wave()
{
	_time = 60;
	_spawnNr = 0;

	_level += 1;
	_strLevel = getLevelstr();
	_waveSpawnVec = loadWaveSpawnVec(_level);
	_timeToNextSpawn = 5;
}

void Wave::setNextSpawn(const int& i)
{
	_timeToNextSpawn += i;
	_spawnNr += 1;
}

bool Wave::isSpawnRead()
{
	return (60 - _time) > _timeToNextSpawn ? true : false;
}

int Wave::tic()
{
	_time -= 1;
	//update info
	_strTime = getTimestr();
	return _time;
}

vector<int> Wave::loadWaveSpawnVec(const int& key)
{
	ifstream inFile("resources/config/WaveConfig.txt");
	string line;
	vector<int> retVec;
	while(std::getline(inFile, line)){
		istringstream isline(line);
		string::size_type mid = line.find("=");
		//find line which corresponds to the level
		if(line.substr(0, mid) == std::to_string(_level)){
			//everything past the "=" sign
			std::string data = line.substr(mid + 1, line.size());
			typedef std::string::iterator iter;
			iter i = data.begin();
			//push back all values in the line
			while(i != data.end()){
				i = std::find_if_not(i, data.end(), isComma);
				iter j = std::find_if(i , data.end(), isComma);
				if(i != data.end()){
					retVec.push_back(std::atoi(std::string(i, j).c_str()));
					i = j;
				}
			}
			typedef vector<int>::size_type it;
			for(it i = 0; i != retVec.size();i++){
				cout << retVec[i] << ",";
			}
			putchar('\n');
			return retVec;
		}
	}
	cout << key << "No key in wave spawn config file" << endl;
	throw;
}


std::string Wave::getTimestr()
{
	return to_string(_time);
}

std::string Wave::getLevelstr()
{
	return to_string(_level);
}

