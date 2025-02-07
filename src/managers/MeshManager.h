#pragma once

#include <unordered_map>
#include <string>

class MeshManager
{
private:
	MeshManager();

public:
	bool StartUp();
	void Shutdown();

	void SetResourceFolder(std::string folderPath) { mMeshFolder = folderPath; }

	class Mesh* GetMesh(std::string fileName);

	static MeshManager* Get();

private:
	std::string mMeshFolder;
	std::unordered_map<std::string, class Mesh*> mMeshes;

};