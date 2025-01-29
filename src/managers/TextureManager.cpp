#include "TextureManager.h"
#include "graphics/Texture.h"
#include "engine/Engine.h"

#include "stb_image.h"

#include <assert.h>

TextureManager::TextureManager() :
	mEngine(Engine::Get())
{}

bool TextureManager::StartUp()
{
	stbi_set_flip_vertically_on_load(false);

	return true;
}

void TextureManager::Shutdown()
{
	for (auto pair : mTextures) 
	{ 
		pair.second->Unload(); 
		delete pair.second;
	}
	mTextures.clear();
}

Texture* TextureManager::GetTexture(std::string fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

TextureManager* TextureManager::Get()
{
	static TextureManager* manager = new TextureManager();
	if (!manager) { manager = new TextureManager(); }
	assert(manager);
	return manager;
}