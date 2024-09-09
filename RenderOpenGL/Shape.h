#pragma once
#include "dlldef.h"
#include "glm/glm.hpp"
#include <vector>

namespace Component
{
	class Shape
	{
	public:
		void Draw();

		CE_RENDEROGL_API void MakeVAO(bool ebo = true);

		//CE_RENDEROGL_API void SetVerticies(float* v, unsigned int c, unsigned int s);

		CE_RENDEROGL_API void SetShape(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& n, const std::vector<glm::ivec3>& i);

		CE_RENDEROGL_API void SetTextureCords(const std::vector<glm::vec2>& t);

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