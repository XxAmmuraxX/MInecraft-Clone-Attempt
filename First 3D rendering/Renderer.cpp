#include "GameManager.h"

Renderer::Renderer(int width, int height, int fps) : screen_height(height), screen_width(width)
{
	InitWindow(width, height, "3D renderering");
	//SetConfigFlags(FLAG_MSAA_4X_HINT);
	//SetConfigFlags(FLAG_VSYNC_HINT);
	//ToggleFullscreen();
}

void Renderer::Render(GameManager& gm, Camera* cam)
{
	BeginDrawing();
	ClearBackground(SKYBLUE);
	BeginMode3D(*cam);


	//DrawGrid(100, 1);

	for (auto& chunk : gm.chunks)
	{
		chunk.Draw(gm.GetPLayerCam()->position);
	}

	//DrawModel(gm.terrain, Vector3Zero(), 1, WHITE);
	//DrawModelEx(gm.plane, Vector3Zero(), { 1,0,0 }, 90, {1,1,1}, WHITE);
	//DrawSphereWires({ 0,0,0 },w 1, 10, 10, GREEN);
	DrawCube({ 0,12,0 }, 1, 1, 1, BLUE);
	DrawCube({ 5,12,0 }, 1, 1, 1, RED);
	DrawCube({ 0,12,5 }, 1, 1, 1, GREEN);
	EndMode3D();
	DrawFPS( 50,50 );
	EndDrawing();
}
