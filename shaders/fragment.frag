#version 330 core

//in vec3 VertexColor;
//in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

out vec4 color;

//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main()
{
	//Ambient
	vec3 ambientComponent = vec3(0.2f);
	
	//Diffuse
	vec3 diffuseComponent = vec3(0.8f);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - Position);
	float diffuse = max(dot(norm, lightDir), 0.0f);
	diffuseComponent = diffuse * diffuseComponent;
	
	//Specular
	vec3 specularComponent = vec3(0.5f);
	vec3 viewDir = normalize(viewPos - Position);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	specularComponent = specular * specularComponent;  
	
	vec3 resultingColor = (ambientComponent+diffuseComponent+specularComponent)*objectColor;
	color = vec4(resultingColor, 1.0f);
}