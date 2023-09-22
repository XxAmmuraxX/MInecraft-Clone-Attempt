#pragma once
#include "Renderer.h"

class Chunk;

class GameManager
{
	Player player{ Vector3{0,12,0},Vector3Zero() };
	Renderer renderer{ 1400,800,144 };
	Model plane = LoadModelFromMesh(GenMeshPlane(1, 1, 1, 1));
	int WORLDSIZE = 20;
	Image noise;
	std::vector<Chunk> chunks;

	friend class Renderer;
public:
	GameManager();
	Camera* GetPLayerCam() { return player.GetCam(); }
	void GenChunks(Image* noise);
	void Update();
	void Render();
	void Run();
};