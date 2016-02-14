#ifndef GUARD_TEXTURE_MANAGER_H
#define GUARD_TEXTURE_MANAGER_H

#include "StdAfx.h"
#include "fileHandler.h"

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();

		void loadAddAll(const char* dirname);
		void loadAdd(std::string filepath);

		sf::Texture& getTexture(std::string key);

	private:
		std::map<std::string, sf::Texture*> _textureMap;

		struct Deallocator
		{
			void operator() (const std::pair<std::string, sf::Texture*>& p) const
			{
				delete p.second;
			}
		};
};

#endif
