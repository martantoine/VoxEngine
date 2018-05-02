#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//INPUT
uniform Material material;
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
	vec3 AmbientLighting = light.ambient * vec3(texture(material.diffuse, fs_in.textureCoord));

	//Diffuse lighting
	float diffuseStrenght = max(dot(normal, lightDir), 0.0);
	vec3 DiffuseLighting = diffuseStrenght * vec3(texture(material.diffuse, fs_in.textureCoord));

	//Specular lighting
	vec3 viewDir = normalize(viewPosition - fs_in.position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 SpecularLighting = spec * light.specular * vec3(texture(material.specular, fs_in.textureCoord));

	//Result
	if(material.diffuse)
		Result = vec4(SpecularLighting + AmbientLighting + DiffuseLighting, 1.0) * fs_in.color * vec4(texture(material.diffuse, fs_in.textureCoord));
	else
		Result = vec4(SpecularLighting + AmbientLighting + DiffuseLighting, 1.0) * (fs_in.color + vec4(texture(material.diffuse, fs_in.textureCoord)));
}