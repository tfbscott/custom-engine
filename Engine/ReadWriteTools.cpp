#include "ReadWriteTools.h"
#include "StreamReadWrite.h"
#include <fstream>

namespace Tools
{

	enum ReadShapeMode
	{
		EMPTY,
		VERTEX,
		NORMAL,
		INDEX,
		TEXTURE
	};

	std::vector<std::string> GetSubstringsFromLine(std::string line, char delimeter = ' ')
	{
		size_t lastCut = 0;
		size_t lineSize = line.size();
		std::vector<std::string> strings;
		for (size_t i = 0; i < lineSize; i++)
		{
			if (line[i] == delimeter)
			{
				std::string subString = line.substr(lastCut, i - lastCut);
				strings.push_back(subString);
				lastCut = i;
			}
		}

		std::string subString = line.substr(lastCut, lineSize - lastCut);
		strings.push_back(subString);

		return strings;
	}

	glm::vec3 GetVec3FromLine(std::string line, char delimeter = ' ')
	{
		std::vector<std::string> numbers = GetSubstringsFromLine(line, delimeter);

		return glm::vec3(std::stof(numbers[0]), std::stof(numbers[1]), std::stof(numbers[2]));
	}

	glm::vec2 GetVec2FromLine(std::string line, char delimeter = ' ')
	{
		std::vector<std::string> numbers = GetSubstringsFromLine(line, delimeter);

		return glm::vec2(std::stof(numbers[0]), std::stof(numbers[1]));
	}

	glm::ivec3 GetIVec3FromLine(std::string line, char delimeter = ' ')
	{
		std::vector<std::string> numbers = GetSubstringsFromLine(line, delimeter);

		return glm::ivec3(std::stoi(numbers[0]), std::stoi(numbers[1]), std::stoi(numbers[2]));
	}

	Component::Shape* ReadShape(std::string boxFile)
	{
		std::fstream fileStream = std::fstream(boxFile, std::fstream::in);

		if (!fileStream.is_open())
		{
			ConsoleWrite("Failed to open file of name");
			ConsoleWrite(boxFile.c_str());
			return nullptr;
		}

		std::vector<glm::vec3> verticies, normals;
		std::vector<glm::ivec3> indicies;
		std::vector<glm::vec2> textureCordinates;

		std::string line, word;
		ReadShapeMode mode = ReadShapeMode::EMPTY;
		//Get a string from the input file
		std::getline(fileStream, line);

		while (!fileStream.eof())
		{
			//If the line denotes we are looking at vertex items
			if (line == "-v")
			{
				mode = VERTEX;
			}
			else if (line == "-n")
			{
				mode = NORMAL;
			}
			else if (line == "-i")
			{
				mode = INDEX;
			}
			else if (line == "-t")
			{
				mode = TEXTURE;
			}
			else if(!line.empty() && line[0] != ';')
			{
				std::vector<std::string> subStrings = GetSubstringsFromLine(line);

				switch (mode)
				{
				case Tools::EMPTY:
					break;
				case Tools::VERTEX:
					glm::vec3 vertex = GetVec3FromLine(line);
					verticies.push_back(vertex);
					break;
				case Tools::NORMAL:
					glm::vec3 normal = GetVec3FromLine(line);
					normals.push_back(normal);
					break;
				case Tools::INDEX:
					glm::ivec3 index = GetIVec3FromLine(line);
					indicies.push_back(index);
					break;
				case Tools::TEXTURE:
					glm::vec2 cordinate = GetVec2FromLine(line);
					textureCordinates.push_back(cordinate);
					break;
				default:
					break;
				}
			}


			std::getline(fileStream, line);
		}

		Component::Shape* shape = new Component::Shape;

		shape->SetShape(verticies, normals, indicies);
		shape->SetTextureCords(textureCordinates);
		shape->MakeVAO();

		
		return shape;
	}
}