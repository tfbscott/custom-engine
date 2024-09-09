#version 330
//layout (location = 0) 
//layout is used to set the order of passed in values
//can use glGetAttribLocation to assist if need be
in vec3 aPos;
in vec2 aTexCoord;

//The tranformation we would like on the model
uniform mat4 model;
//The World Projection
uniform mat4 projection;
//The World View
uniform mat4 view;

out vec4 worldNorm;
out vec2 TexCoord;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0f);
   
   TexCoord = aTexCoord;
}

