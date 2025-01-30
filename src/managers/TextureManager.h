#pragma once

#include <unordered_map>
#include <string>

class TextureManager
{
private:
	TextureManager();

public:
	bool StartUp();
	void Shutdown();

	class Texture* GetTexture(std::string fileName);

	static TextureManager* Get();

private:
	std::unordered_map<std::string, class Texture*> mTextures;

};