#version 330

in vec2 uv;

out vec4 fragColor;

void main()
{

	vec3 col = vec3(0,0,0);

	if(uv.x < 0.5)
		col.x = 1.f;
	else
		col.x = 0.5;
	col.y = 0.5;
	col.z = 0.5;

	fragColor = vec4(col,1);
}