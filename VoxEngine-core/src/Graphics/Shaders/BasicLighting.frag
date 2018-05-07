#version 330 core

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//INPUT
uniform bool textured;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

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


float near = 0.005; 
float far  = 10.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far + near));	
}


void main()
{
	//Commons
	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(viewPosition - fs_in.position);
	
	//Ambient lighting
	vec3 AmbientLighting;
	if(textured)
		AmbientLighting = light.ambient * vec3(texture(texture_diffuse1, fs_in.textureCoord));
	else
		AmbientLighting = light.ambient;

	//Diffuse lighting
	float diffuseStrenght = max(dot(normal, lightDir), 0.0);
	vec3 DiffuseLighting;
	if(textured)
		DiffuseLighting = diffuseStrenght * light.diffuse * vec3(texture(texture_diffuse1, fs_in.textureCoord));
	else
		DiffuseLighting = diffuseStrenght * light.diffuse;

	//Specular lighting
	vec3 viewDir = normalize(viewPosition - fs_in.position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 SpecularLighting;
	if(textured)
		SpecularLighting = spec * light.specular * vec3(texture(texture_specular1, fs_in.textureCoord));
	else
		SpecularLighting = spec * light.specular;
	
	Result = vec4(DiffuseLighting + AmbientLighting + SpecularLighting, 1.0f) * fs_in.color;
	
	float depth = LinearizeDepth(gl_FragCoord.z);
    //Result = Result * vec4(vec3(depth), 1.0);
}