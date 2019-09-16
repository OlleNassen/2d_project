#include "drawer.h"
#include "shader.h"
#include "glad/glad.h"
#include "window.h"

void drawer_initialize(Drawer& drawer, const char* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns)
{
	tilemap_generate(drawer.tilemap, type_data, num_tiles_rows, num_tiles_columns, 32, 32);

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

	drawer.texture = texture_from_file("cursor.png");
	drawer.player_texture = texture_from_file("isometric_hero_dezrasdragons.png");
}

void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], Vector2& cursor_pos)
{
	glUseProgram(drawer.shader_tex);
	shader_uniform(drawer.shader_tex, "view", vector2_create(camera.position.x, camera.position.y));
	shader_uniform(drawer.shader_tex, "projection", camera.ortho);
	shader_uniform(drawer.shader_tex, "sprite_tex", 0);
	tilemap_draw(drawer.tilemap);

	glBindVertexArray(drawer.sprite_vao);
	for (int i = 0; i < 4; ++i)
	{
		Rect rect = rect_create(team_positions[i].x, team_positions[i].y, 200, 200);
		SpriteAnimation anim;
		anim.speed = 0.5f;
		anim.sprite = rect_create(0, 0, 32, 32);
		anim.size = rect_create(0, 0, 24 * 3, 32);

		float time = window_time_get();
		glDisable(GL_DEPTH_TEST);
		sprite_draw(&rect, &anim, &drawer.player_texture, time);
		glEnable(GL_DEPTH_TEST);
	}

	Vector2 conv_pos = vector2_create(cursor_pos.x + 16, cursor_pos.y + 16);
	conv_pos = cart_to_dimetric(conv_pos);
	Rect rect = rect_create(conv_pos.x, conv_pos.y, 32 * 4, 32 * 4);
	SpriteAnimation anim;
	anim.speed = 0.0f;
	anim.sprite = rect_create(0, 0, 32, 32);
	anim.size = rect_create(0, 0, 32, 32);

	float time = window_time_get();
	glDisable(GL_DEPTH_TEST);
	sprite_draw(&rect, &anim, &drawer.texture, time);
	glEnable(GL_DEPTH_TEST);
}

void drawer_draw_build(Drawer & drawer, Camera & camera, char* names[4])
{
	Rect rect = rect_create(camera.position.x + 1280 / 2, camera.position.y + 720 / 2, 1280, 720);
	SpriteAnimation anim;
	anim.speed = 0.5f;
	anim.sprite = rect_create(0, 0, 32, 32);
	anim.size = rect_create(0, 0, 24 * 3, 32);

	float time = window_time_get();
	glDisable(GL_DEPTH_TEST);
	sprite_draw(&rect, &anim, &drawer.player_texture, time);
	glEnable(GL_DEPTH_TEST);
}

void drawer_draw_mainmenu(Drawer & drawer, Camera & camera)
{

}
