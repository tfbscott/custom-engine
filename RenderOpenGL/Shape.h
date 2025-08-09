#pragma once
#include "glm/glm.hpp"
#include <vector>

namespace Component
{
	class Shape
	{
	public:
		void Draw();

		void MakeVAO(bool ebo = true);

		//CE_RENDEROGL_API void SetVerticies(float* v, unsigned int c, unsigned int s);

		void SetShape(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& n, const std::vector<glm::ivec3>& i);

		void SetTextureCords(const std::vector<glm::vec2>& t);

	protected:
		unsigned int VAOID;

		//unsigned int VBOID;

		bool useEBO;
		//unsigned int EBOID;


		unsigned int count;

		unsigned int stride;

		//New list of verts
		std::vector<glm::vec3> vert;
		//New list of normals
		std::vector<glm::vec3> norm;
		//Indicies for EBO
		std::vector<glm::ivec3> ind;

		std::vector<glm::vec2> tex;
	};
}