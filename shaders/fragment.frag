#version 330 core

in vec3 vertexColor;
out vec4 color;
//uniform vec4 ourColor;
void main()
{
	color = vec4(vertexColor, 1.0);
}
