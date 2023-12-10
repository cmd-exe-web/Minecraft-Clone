#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(std::string filePath)
	:m_FilePath(filePath), m_Id(0)
{
	m_Id = CreateShader();
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Bind()
{
	glUseProgram(m_Id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 vec)
{
	glUniform3fv(GetUniformLocation(name), 3, &vec.x);
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4fv(const std::string& name, glm::vec4 vec)
{
	glUniform4fv(GetUniformLocation(name), 1, &vec[0]);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}



unsigned int Shader::CreateShader()
{
	auto [vertexSource, fragmentSource] = ParseShader();

	GLuint program = glCreateProgram();

	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length);
		glGetProgramInfoLog(program, length, &length, message);

		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);

		std::cout << "Linking Failed!" << std::endl;
		std::cout << message << std::endl;
		return -1;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

std::pair<std::string, std::string> Shader::ParseShader()
{
	std::ifstream stream(m_FilePath);
	std::string line;
	std::stringstream ss[2];

	enum class ShaderType {
		NONE = -1, VERTEX, FRAGMENT
	};
	ShaderType type = ShaderType::NONE;

	if (stream.is_open()) {
		while (std::getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
			else {
				ss[(int)type] << line << '\n';
			}
		}
	}

	return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& shaderSource)
{
	GLuint shader = glCreateShader(shaderType);
	const char* src = shaderSource.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length);
		glGetShaderInfoLog(shader, length, &length, message);
		
		std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_Id, name.c_str());
	if (location == -1)
        std::cerr << "Warning: Cannot find '" << name << "'/uniform not in use" << std::endl;
	return location;
}


