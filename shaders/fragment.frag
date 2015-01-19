#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	float reflectivity;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	//Spatial
	vec3 position;
	
	//Phong
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//Attenuation
	float constant;
	float linear;
	float quadratic; 
};

struct SpotLight {
	//Spatial
	vec3 position;
	vec3 direction;
	
	//Spot
	float spotCutOff;
	float spotOuterCutOff;
	
	//Phong
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//Attenuation
	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 4

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;


uniform vec3 viewPos;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - Position);
	
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
	for(int i = 0; i<NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, Position, viewDir);
	}
	result += CalcSpotLight(spotLight, norm, Position, viewDir);
	color = vec4(result, 1.0f);
}


vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
	vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * light.diffuse * diff;
	vec3 specular = vec3(texture(material.diffuse, TexCoords)) * light.specular * spec;
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position-Position);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	float distance = length(light.position-Position);
	float attenuation = 1.0f / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
		
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
	vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * light.diffuse * diff;
	vec3 specular = vec3(texture(material.diffuse, TexCoords)) * light.specular * spec;
	
	return (ambient + diffuse + specular)*attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position-Position);
	vec3 reflectDir = reflect(-lightDir, normal);  
	
	float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.spotCutOff - light.spotOuterCutOff);                                                                                                               
    float intensity = clamp((theta - light.spotOuterCutOff)/epsilon, 0.0, 1.0);
	
	float distance = length(light.position-Position);
	float attenuation = 1.0f / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
	
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * light.diffuse * diff;
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.diffuse, TexCoords)) * light.specular * spec;

	return (ambient + diffuse + specular)*attenuation;
}
