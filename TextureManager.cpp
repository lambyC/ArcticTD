#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for_each(_textureMap.begin(), _textureMap.end(), Deallocator());
}

void TextureManager::loadAddAll(const char* dirname)
{
	//Find all directories in given location
	vector<string> directories = fill_vec_filepath(dirname);
	vector<vector<string> > filepath;
	//Find all files in those directories
	for(vector<vector<string> >::size_type i = 0; i != directories.size(); i++){
		filepath.push_back(fill_vec_filepath((dirname + directories[i]).c_str()));
	}
	//Load all files into map
	for(vector<vector<string> >::size_type i = 0; i != filepath.size(); i++){
		for(std::vector<std::string>::size_type n = 0; n != filepath[i].size(); n++){
			loadAdd(dirname + directories[i] + '/' + filepath[i][n]);
		}
	}
	//TODO make more generic, check if file is .png.
}

void TextureManager::loadAdd(string filepath)
{
	sf::Texture* texture = new sf::Texture();

	//Split filepath up at backslah and add to vector
	//last position in vector is the filename which we use as key
	vector<string> split_filepath = split_backslash(filepath);

	texture->loadFromFile(filepath);
	//get last string in vec aka the filename
	_textureMap.insert(pair<string, sf::Texture*>(split_filepath.back(), texture));
}

sf::Texture& TextureManager::getTexture(string key)
{
	map<string, sf::Texture*>::iterator result = _textureMap.find(key);
	if(result == _textureMap.end()){
		cout << key << endl;
		throw key;
	}
	return *result->second;
}


