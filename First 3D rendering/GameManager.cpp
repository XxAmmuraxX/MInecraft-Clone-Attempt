#include "GameManager.h"

GameManager::GameManager()
{
	//mat.maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	//cube.materials[0] = mat;
	//terrain.materials[0] = mat;
	//plane.materials[0] = mat;

	noise = GenImagePerlinNoise(2048, 2048, 0, 0, 20);

	Block::LoadTextures();

	GenChunks(&noise);
}

void GameManager::GenChunks(Image* noise)
{
	for (int z = 0; z < WORLDSIZE; z++)
	{
		for (int x = 0; x < WORLDSIZE; x++)
		{
			chunks.push_back(Chunk(Vector3{ x / 1.f,0,z / 1.f }, noise, &plane));
		}
	}
	
	for (int z = 0; z < WORLDSIZE; z++)
	{
		for (int x = 0; x < WORLDSIZE; x++)
		{
			if (x != 0)
				chunks[x + z * WORLDSIZE].AddFrontChunk(&chunks[x - 1 + z * WORLDSIZE]);
			if (x != WORLDSIZE - 1)
				chunks[x + z * WORLDSIZE].AddBackChunk(&chunks[x + 1 + z * WORLDSIZE]);
			if (z != 0)
				chunks[x + z * WORLDSIZE].AddLeftChunk(&chunks[x + (z - 1) * WORLDSIZE]);
			if (z != WORLDSIZE - 1)
				chunks[x + z * WORLDSIZE].AddRightChunk(&chunks[x + (z + 1) * WORLDSIZE]);
		}
	}

}

void GameManager::Update()
{
	player.Update();
}

void GameManager::Render()
{
	renderer.Render(*this, GetPLayerCam());
}

void GameManager::Run()
{
	while (!WindowShouldClose())
	{
		Update();
		Render();
	}
}
