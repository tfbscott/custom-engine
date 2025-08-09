#pragma once

namespace Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram();

		void CompileShaderFromFile(const char* file, int shaderType);

		void LinkProgram();

		void UseProgram();

		~ShaderProgram();

	
		unsigned int programID;

	private:
	};
}