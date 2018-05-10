#version 330 core

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//INPUT
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform int textured;
uniform int UI;

uniform Light light;
uniform vec3 viewPosition;

float near = 0.5; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

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
	if(UI)
	{
		vec4 texColor = texture(texture_diffuse1, fs_in.textureCoord);
		if(texColor.r < 0.1)
			discard;
		Result = texColor * fs_in.color;
	}
	else
	{
			//Ambient lighting
		vec3 AmbientLighting;
		if(textured == 1)
			AmbientLighting = light.ambient * texture(texture_diffuse1, fs_in.textureCoord).rgb;
		else
			AmbientLighting = light.ambient;

		//Diffuse lighting
		vec3 normal = normalize(fs_in.normal);
		vec3 lightDir = normalize(viewPosition - fs_in.position);
		float diffuseStrenght = max(dot(normal, lightDir), 0.0);
		vec3 DiffuseLighting;
		if(textured == 1)
			DiffuseLighting = light.diffuse * diffuseStrenght * texture(texture_diffuse1, fs_in.textureCoord).rgb;
		else
			DiffuseLighting = light.diffuse * diffuseStrenght;

		//Specular lighting
		vec3 viewDir = normalize(viewPosition - fs_in.position);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = sqrt(tan(pow(max(dot(viewDir, reflectDir), 0.0), 128)));
		
		vec3 SpecularLighting;
		if(textured == 1)
			SpecularLighting = spec * light.specular * texture(texture_specular1, fs_in.textureCoord).rgb;
		else
			SpecularLighting = spec * light.specular;

		float depth = 100 / LinearizeDepth(gl_FragCoord.z);
		Result = vec4(AmbientLighting + DiffuseLighting + SpecularLighting, 1.0f) * fs_in.color;
	}
}