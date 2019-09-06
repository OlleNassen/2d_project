#include "drawer.h"
#include "shader.h"
#include "glad/glad.h"
#include "window.h"


void drawer_initialize(Drawer& drawer)
{
	tilemap_generate(drawer.tilemap, 64, 32, 32, 32);

	drawer.shader = shader_create("resources/shaders/2d.vert", "resources/shaders/2d.frag");
	drawer.shader_tex = shader_create("resources/shaders/2dtex.vert", "resources/shaders/2dtex.frag");

	glGenVertexArrays(1, &drawer.sprite_vao);
	glBindVertexArray(drawer.sprite_vao);
	glGenBuffers(1, &drawer.sprite_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.sprite_vbo);
	glBufferData(GL_ARRAY_BUFFER, 128, 0, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	float *pointer = 0;
	unsigned int stride = sizeof(float) * 4;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, pointer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, pointer + 2);

	drawer.texture = texture_from_file("test.png");
}

void drawer_draw(Drawer& drawer, Camera& camera)
{
	glUseProgram(drawer.shader);
	shader_uniform(drawer.shader, "view", vector2_create(camera.position.x, camera.position.y));
	shader_uniform(drawer.shader, "projection", camera.ortho);
	tilemap_draw(drawer.tilemap);

	Rect rect = rect_create(150, 150, 200, 200);
	SpriteAnimation anim;
	anim.speed = 0.5f;
	anim.sprite = rect_create(0, 0, 24, 32);
	anim.size = rect_create(0, 0, 24 * 3, 32);

	glUseProgram(drawer.shader_tex);
	glBindVertexArray(drawer.sprite_vao);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.sprite_vbo);

	shader_uniform(drawer.shader_tex, "view", vector2_create(camera.position.x, camera.position.y));
	shader_uniform(drawer.shader_tex, "projection", camera.ortho);
	shader_uniform(drawer.shader_tex, "sprite_tex", 0);

	float time = window_time_get();
	sprite_draw(&rect, &anim, &drawer.texture, time);
}
