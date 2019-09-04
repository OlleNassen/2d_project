#version 330

in vec2 uv;

out vec4 fragColor;

uniform vec3 color;

void main()
{
	vec3 col = color / 255;
	vec3 finalColor = vec3(normalize(uv), 1) * col;
	fragColor = vec4(1,1,0,1);
}