#version 330

in vec2 uv;

out vec4 frag;

uniform sampler2D sprite_tex;

void main()
{
	frag = vec4(texture(sprite_tex, uv).xyz, 1.0);
	//frag = vec4(1);
}