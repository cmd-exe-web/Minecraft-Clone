#pragma once

#include <string>
#include <utility>

#include "glm/glm.hpp"

class Shader {
public:
	Shader(std::string filePath);
	~Shader();

	void Bind();
	void Unbind();

	// Uniforms
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3fv(const std::string& name, glm::vec3 vec);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4fv(const std::string& name, glm::vec4 vec);
	void SetUniformMat4(const std::string& name, glm::mat4 mat);
private:
	unsigned int m_Id;
	std::string m_FilePath;
	// Caching

private:
	unsigned int CreateShader();
	std::pair<std::string, std::string> ParseShader();
	unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSource);

	int GetUniformLocation(const std::string& name);
};

