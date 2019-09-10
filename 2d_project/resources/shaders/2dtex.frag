#version 330

in vec2 uv;

out vec4 frag;

uniform sampler2D sprite_tex;

void main()
{
	frag = texture(sprite_tex, uv);
	//frag = vec4(1);
}