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

	void SetResourceFolder(std::string folderPath) { mResFolder = folderPath; }

	class Texture* GetTexture(std::string fileName);

	static TextureManager* Get();

private:
	std::string mResFolder;
	std::unordered_map<std::string, class Texture*> mTextures;

};