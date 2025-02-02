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

	void SetResourceFolder(std::string folderPath) { mTexFolder = folderPath; }

	class Texture* GetTexture(std::string fileName);

	static TextureManager* Get();

private:
	std::string mTexFolder;
	std::unordered_map<std::string, class Texture*> mTextures;

};