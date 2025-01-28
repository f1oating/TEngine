#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

class Skeleton
{
public:
	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mBones.size(); }
	const struct Bone& GetBone(size_t idx) const { return mBones[idx]; }
	const std::vector<struct Bone>& GetBones() const { return mBones; }
	const std::vector<glm::mat4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
	const std::string& GetFileName() const { return mFileName; }

protected:
	void ComputeGlobalInvBindPose();

private:
	std::vector<struct Bone> mBones;
	std::vector<glm::mat4> mGlobalInvBindPoses;
	std::string mFileName;

};