#pragma once

namespace Component
{
	class Texture
	{
	public:

		Texture();

		void Read(const char* n, bool flip = false);

		void BindTexture();

		void UnbindTexture();

	private:
		int width;

		int height;

		int colorChannels;

		unsigned int textureID;
	};
}