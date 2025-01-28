#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Animation
{
public:
	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mNumBones; }
	size_t GetNumFrames() const { return mNumFrames; }
	float GetDuration() const { return mDuration; }
	float GetFrameDuration() const { return mFrameDuration; }

	const std::string& GetFileName() const { return mFileName; }
	void GetGlobalPoseAtTime(std::vector<glm::mat4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

private:
	size_t mNumBones;
	size_t mNumFrames;
	float mDuration;
	float mFrameDuration;

	std::vector<std::vector<class BoneTransform>> mTracks;
	std::string mFileName;
};