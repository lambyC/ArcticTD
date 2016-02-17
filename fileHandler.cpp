#include "fileHandler.h"

using namespace std;

vector<string> split_backslash(const string& str)
{
	typedef string::const_iterator iter;	
	iter i = str.begin();
	vector<string> retVec;
	while(i != str.end()){
		i = find_if_not(i, str.end(), isBackslash);
		iter j = find_if(i, str.end(), isBackslash);
		if(i != str.end()){
			retVec.push_back(string(i, j));
		}
		i = j;
	}
	return retVec;
}

vector<string> fill_vec_filepath(const char* dirname)
{
	DIR* dir;
	struct dirent *ent;

	vector<string> retVec;

	if((dir = opendir(dirname)) != NULL ){
		while((ent = readdir(dir)) != NULL){
			if(std::strcmp(ent->d_name,".") != 0 && std::strcmp(ent->d_name,"..") != 0){
				retVec.push_back(ent->d_name);
			}
		}
		closedir(dir);
	}
	return retVec;
}
