#version 330

in vec2 uv;
in float z;

out vec4 frag;

uniform sampler2D sprite_tex;

void main()
{
	frag = texture(sprite_tex, uv);
	if(frag == vec4(1.0, 1.0,1.0,1.0) || frag == vec4(1 / 255.f,1 / 255.f,1 / 255.f,1))
		discard;
}