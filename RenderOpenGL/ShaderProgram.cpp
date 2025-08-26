#include "pch.h"
#include "ShaderProgram.h"
#include "StreamReadWrite.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics
{
	ShaderProgram::ShaderProgram() : programID(0)
	{
		programID = glCreateProgram();
		int success;
		glGetShaderiv(programID, GL_LINK_STATUS, &success);

		if (!success)
		{
			//SOMETHING BROKE
			Tools::ConsoleWrite("Failed to link shader program");
		}
	}


	void ShaderProgram::CompileShaderFromFile(const char* file, int shaderType)
	{
		unsigned int shader = 0;
		std::string source = Tools::ReadFile(file);

		if (!source.empty())
		{
			shader = glCreateShader(shaderType);
			const char* sourceCString = source.c_str();
			glShaderSource(shader, 1, &sourceCString, NULL);
			glCompileShader(shader);
			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				//SOMETHING BROKE
				char log[512];
				glGetShaderInfoLog(shader, 512, NULL, log);
				Tools::ConsoleWrite("Failed to compile a shader");
				Tools::ConsoleWrite(log);
			}

			glAttachShader(programID, shader);

			//glDeleteShader(shader);
		}
	}

	void ShaderProgram::LinkProgram()
	{
		glLinkProgram(programID);

		int success;
		glGetShaderiv(programID, GL_LINK_STATUS, &success);

		if (!success)
		{
			//SOMETHING BROKE
			Tools::ConsoleWrite("Failed to link shader program");
		}
	}

	void ShaderProgram::UseProgram()
	{
		glUseProgram(programID);
	}


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programID);
	}
}