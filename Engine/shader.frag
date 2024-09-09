#version 330
out vec4 FragColor;

in vec4 worldNorm;

in vec2 TexCoord;

uniform vec3 color;

uniform int useTex;

uniform sampler2D tex;

void main()
{
	if(useTex == 1)
		FragColor = texture(tex, TexCoord);
	else
		FragColor = glm::vec4(color, 1.0f);
}