#pragma once
#include "Player.h"

class GameManager;

class Renderer
{
	int screen_width, screen_height;
	std::vector<Color> color_bank;

public:
	Renderer(int width, int height, int fps);
	void Render(GameManager& gm, Camera* cam);
};