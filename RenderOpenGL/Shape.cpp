#include "pch.h"
#include "Shape.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "glm/gtc/type_ptr.hpp"

namespace Component
{
	void Shape::Draw()
	{
		glBindVertexArray(VAOID);
		if (useEBO)
		{
			glDrawElements(GL_TRIANGLES, 3 * count, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
		//Unbind the array
		glBindVertexArray(0);
	}

	void Shape::MakeVAO(bool ebo)
	{
		useEBO = ebo;

		//Create the Vertex Array Object
		glGenVertexArrays(1, &VAOID);
		//Bind the VAO, so the data is stored in it
		glBindVertexArray(VAOID);

		GLuint VBOID;
		//Create a vertex Buffer Objectr
		glGenBuffers(1, &VBOID);
			
		//Bind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);
		//Configure the VBO
		//first param is type of buffer
		//second is size of data
		//third is the data
		//forth is how we want th graphics card to manage the data
		/*
		GL_STREAM_DRAW: data set once and used a few times
		GL_STATIC_DRAW: data set once and used many times
		GL_DYNAMIC_DRAW: data is changed a lot and used many times
		*/
		glBufferData(GL_ARRAY_BUFFER, /*sizeof(vertices)*/vert.size() * stride * sizeof(float), &vert[0][0], GL_STATIC_DRAW);

		//Tell OpenGL how to interpret the vertex gata
		/*
		First parameter is which vertex attribute we want to configure, vertex shader layout = 0, so 0
		Second is size of the vertex attribute (vec3)
		Third is type of data
		Forth is if we want the data to be normalized
		Fith is stride, or space between consecutive vertex attributes (0 since values are packed)
		Final is offset of where the position starts (posistion data is at front of array so value is just 0)
		*/
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//Set up the normal array

		
		//Generate an array for texture coords
		if (tex.size() > 0)
		{
			GLuint TEXID;
			//Generate the buffer
			glGenBuffers(1, &TEXID);
			//Bind the buffer
			glBindBuffer(GL_ARRAY_BUFFER, TEXID);
			//Configure the texture buffer
			//Size is multiplided by 2 because its a vec2
			glBufferData(GL_ARRAY_BUFFER, tex.size() * sizeof(float) * 2, &tex[0][0], GL_STATIC_DRAW);
			//Enable the vertex attrribute
			//1 is the location we want to grab in the vertex shader code
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		//If asked to, copy the indicies data into a element buffer object
		if (ebo)
		{
			GLuint EBOID;

			glGenBuffers(1, &EBOID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * ind.size(), &ind[0][0], GL_STATIC_DRAW);
			count = ind.size();
		}

		
	}

	/*void Shape::SetVerticies(float* v, unsigned int c, unsigned int s)
	{
		vertices = v;
		count = c;
		stride = s;
	}*/

	void Shape::SetShape(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& n, const std::vector<glm::ivec3>& i)
	{
		vert = v;
		ind = i;
		stride = 3;
	}

	void Shape::SetTextureCords(const std::vector<glm::vec2>& t)
	{
		tex = t;
	}
}