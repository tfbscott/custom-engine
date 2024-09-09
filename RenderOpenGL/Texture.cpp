#include "pch.h"
#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Component
{

	Texture::Texture() : width(0), height(0), colorChannels(0),  textureID(0)
	{

	}

	void Texture::Read(const char* n, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(n, &width, &height, &colorChannels, 0);

		//Store the texture into a glfw ID
		//First param is number of textures
		//Second is ID
		glGenTextures(1, &textureID);

		//Bind texture commands
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Set some texture parameters
		//BY AXIS
		//Wrapping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		
		//Filtering Settings
		//Currently if smaller, linearly interp between two mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//If larger, just use closest image (give pixel-ish look, use GL_LINEAR for smooth)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//Generate the texture
		/*Params
		* Which bound texture type we are looking for
		* What mipmap level we want to create a texture for (leave at 0 for auto)
		* How do we want to store the texture (RGB)
		* Width of texture
		* Height of texture
		* Always 0 (legacy stuff I guess)
		* Format of image (RGB)
		* Datatype
		* Actual data
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Now we can delete the stbi data;
		stbi_image_free(data);
	}

	void Texture::BindTexture()
	{
		//Bind the texture into a certain unit (currently unit 0)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture::UnbindTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}