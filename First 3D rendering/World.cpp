#include "World.h"
#include <iostream>

Chunk::Chunk(Vector3 pos, Image* noise, Model* block_face) : pos(pos)
{
	if (!plane) plane = block_face;
	this->pos.x *= CHUNK_WIDTH;
	this->pos.z *= CHUNK_WIDTH;
	this->pos.y *= CHUNK_HEIGHT;

	Generate(noise);
}

void Chunk::Generate(Image* noise)
{
	for (int y = 0; y < CHUNK_HEIGHT; y++)
		for (int x = 0; x < CHUNK_WIDTH; x++)
			for (int z = 0; z < CHUNK_WIDTH; z++)
			{
				float perlin_value = (float)GetImageColor(*noise,pos.x + x, pos.z + z).r / 255.0f;

				float ground_height = 1 + perlin_value * (CHUNK_HEIGHT - 1);

				int id = 0;
				if (y < CHUNK_HEIGHT / 3) id = 2;
				if (y > ground_height) id = -1;
				if (y < ground_height - 1 && y > ground_height - 4) id = 1;
				if (y == ground_height) id = 0;
				blocks[x][y][z] = Block(intVec3{ x, y, z }, id);
			}
}

void Chunk::Draw(Vector3 &player_pos)
{
	Vector2 chunk2D_pos = Vector2{ pos.x,pos.z };
	Vector2 chunk_center = Vector2Add(chunk2D_pos, Vector2{ CHUNK_WIDTH / 2.0f,CHUNK_WIDTH / 2.0f });
	Vector2 player2D_pos = Vector2{ player_pos.x, player_pos.z };

	unsigned int RENDER_DISTANCE = 3;
	if (Vector2Distance(player2D_pos, chunk_center) > RENDER_DISTANCE*CHUNK_WIDTH) return;

	for (int y = 0; y < CHUNK_HEIGHT; y++)
		for (int x = 0; x < CHUNK_WIDTH; x++)
			for (int z = 0; z < CHUNK_WIDTH; z++)
			{
				Vector3 pos = Vector3Add(this->pos, Vector3{(float)x, (float)y, (float)z});
				Vector3 top = Vector3Add(pos,{ 0, 0.5, 0 });
				Vector3 right = Vector3Add(pos, { 0,0,0.5 });
				Vector3 bottom = Vector3Add(pos, { 0,-0.5,0 });
				Vector3 left = Vector3Add(pos, { 0,0,-0.5 });
				Vector3 front = Vector3Add(pos, { -0.5,0,0 });
				Vector3 back = Vector3Add(pos, { 0.5,0,0 });
			
				if (blocks[x][y][z].id < 0) continue;
				plane->materials[0] = block_material;
				


				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().right;
				plane->transform = MatrixRotateXYZ({ PI / 2,0,0 });


				if (z == CHUNK_WIDTH - 1)
				{
					if (right_chunk && right_chunk->blocks[x][y][0].id == -1)
						DrawModel(*plane, right, 1, WHITE);
				}
				else if (blocks[x][y][z + 1].id == -1)
				{
					DrawModel(*plane, right, 1, WHITE);
				}
				

				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().back;
				plane->transform = MatrixRotateZYX({ PI/2,PI/2,0 });

				if (x == CHUNK_WIDTH - 1)
				{
					if (back_chunk && back_chunk->blocks[0][y][z].id == -1)
						DrawModel(*plane, back, 1, WHITE);
				}
				else if (blocks[x + 1][y][z].id == -1)
				{
					DrawModel(*plane, back, 1, WHITE);
				}
				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().left;
				plane->transform = MatrixRotateZYX({ PI/2,PI,0 });

				if (z == 0)
				{
					if (left_chunk && left_chunk->blocks[x][y][CHUNK_WIDTH - 1].id == -1)
						DrawModel(*plane, left, 1, WHITE);
				}
				else if (blocks[x][y][z - 1].id == -1)
				{
					DrawModel(*plane, left, 1, WHITE);
				}

				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().front;
				plane->transform = MatrixRotateZYX({ PI/2,-PI / 2,0 });

				if (x == 0)
				{
					if (front_chunk && front_chunk->blocks[CHUNK_WIDTH - 1][y][z].id == -1)
						DrawModel(*plane, front, 1, WHITE);
				}
				else if (blocks[x - 1][y][z].id == -1)
				{
						DrawModel(*plane, front, 1, WHITE);
				}

				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().top;
				plane->transform = MatrixRotateXYZ({ 0,0,0 });

				if (y == CHUNK_HEIGHT - 1)
				{
					DrawModel(*plane, top, 1, WHITE);
				}
				else if (blocks[x][y + 1][z].id == -1)
				{
					DrawModel(*plane, top, 1, WHITE);
				}

				block_material.maps[MATERIAL_MAP_DIFFUSE].texture = blocks[x][y][z].GetTexture().bottom;
				plane->transform = MatrixRotateXYZ({ PI,0,0 });


				if (y == 0)
				{
					//DrawModelEx(plane, bottom, { 1,0,0 }, 180, { 1,1,1 }, WHITE);
				}
				else if (blocks[x][y - 1][z].id == -1)
				{
					DrawModel(*plane, bottom, 1, WHITE);
				}

			}
}

void Chunk::DrawV2()
{
}


void Block::LoadTextures()
{
	block_textures.push_back(LoadTexture("textures/grass_top.png"));
	block_textures.push_back(LoadTexture("textures/grass_side.png"));
	block_textures.push_back(LoadTexture("textures/dirt.png"));
	block_textures.push_back(LoadTexture("textures/stone.png"));
	block_material = LoadMaterialDefault();
}

Block::Block()
{
	pos = { 0,0,0 };
	id = 0;
}

TextureFaces Block::GetTexture()
{
	TextureFaces faces;


	if (id == 0)
	{
		faces.AllSides(block_textures[1]);
		faces.top = block_textures[0];
		faces.bottom = block_textures[2];
	}

	if (id == 1)
	{
		faces.AllFaces(block_textures[2]);
	}

	if (id == 2)
	{
		faces.AllFaces(block_textures[3]);
	}

	return faces;
}
