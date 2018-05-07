#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 textureCoord;

uniform float explosion;
uniform mat4 model; 
uniform mat4 view;
uniform mat4 projection;

out DATA
{
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 textureCoord;
} vs_out;

void main()
{
	gl_Position = projection * view * model * vec4(position +  normal * (explosion - 1.0), 1.0f);
	vs_out.normal = mat3(inverse(transpose(model))) * normal;
	vs_out.position = vec3(model * vec4(position + normal * explosion, 1.0));
	vs_out.color = vec4(color, 1.0f);
	vs_out.textureCoord = textureCoord;
}