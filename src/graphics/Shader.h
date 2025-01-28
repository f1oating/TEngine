#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const glm::mat4& matrix);
	void SetMatrixUniforms(const char* name, glm::mat4* matrices, unsigned count);
	void SetVectorUniform(const char* name, const glm::vec3& vector);
	void SetFloatUniform(const char* name, float value);

private:
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

private:
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;

};