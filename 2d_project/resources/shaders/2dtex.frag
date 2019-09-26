#version 440

in vec2 uv;
in vec3 color;
in float z;

out vec4 frag;
out float gl_FragDepth;

layout(location = 3)uniform sampler2D sprite_tex;

void main()
{
	frag = texture(sprite_tex, uv) * vec4(color, 1.0);
	if(frag == vec4(0,0,0,0) || frag == vec4(1,1,1,1))
		discard;
	gl_FragDepth = z;
}