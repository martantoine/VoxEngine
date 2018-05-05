#version 330 core

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//INPUT
uniform int shininess;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform Light light;
uniform vec3 viewPosition;

in DATA
{
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 textureCoord;
} fs_in;

//OUTPUT
out vec4 Result;

void main()
{
	//Commons
	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(light.position - fs_in.position);

	//Ambient lighting
	vec3 AmbientLighting = light.ambient * vec3(mix(texture(texture_diffuse1, fs_in.textureCoord), texture(texture_diffuse2, fs_in.textureCoord), 0.5));

	//Diffuse lighting
	float diffuseStrenght = max(dot(normal, lightDir), 0.0);
	vec3 DiffuseLighting = diffuseStrenght * vec3(mix(texture(texture_diffuse1, fs_in.textureCoord), texture(texture_diffuse2, fs_in.textureCoord), 0.5));

	//Specular lighting
	vec3 viewDir = normalize(viewPosition - fs_in.position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 SpecularLighting = spec * light.specular * vec3(mix(texture(texture_specular1, fs_in.textureCoord), texture(texture_specular2, fs_in.textureCoord), 0.5));

	
	Result = vec4(SpecularLighting + AmbientLighting + DiffuseLighting, 1.0f) * fs_in.color;
	//Result = texture(texture_specular, fs_in.textureCoord);
}