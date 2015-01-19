#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	float reflectivity;
	float shininess;
};

struct Light {
	// vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;



void main()
{
	//Properties
	//vec3 norm = normalize(texture2D(material.normal, TexCoords).rgb * 2.0 -1.0);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	vec3 viewDir = normalize(viewPos - Position);
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	//Ambient
	vec3 ambientLight = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
	
	//Diffuse
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseLight = vec3(texture(material.diffuse, TexCoords)) * diffuseStrength * light.diffuse;
	
	//Specular
	float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess)*material.reflectivity;
	vec3 specularLight = vec3(texture(material.specular, TexCoords)) * specularStrength * light.specular;
	
	vec3 combinedLight = (ambientLight + diffuseLight + specularLight);
	color = vec4(combinedLight, 1.0f);
}