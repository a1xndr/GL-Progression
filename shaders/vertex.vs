// Vertex shader:
// ================
#version 130 
in vec3 position;
in vec3 normal;
in vec2 texCoords;

out vec2 TexCoords;
out vec3 fragPosition;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    fragPosition = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;
}