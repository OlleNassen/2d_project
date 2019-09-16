#version 330

in vec2 uv;
in float z;

out vec4 frag;
out float gl_FragDepth;

uniform sampler2D sprite_tex;

void main()
{
	frag = texture(sprite_tex, uv);
	if(frag == vec4(0,0,0,0) || frag == vec4(1,1,1,1))
		discard;
	gl_FragDepth = z;
}