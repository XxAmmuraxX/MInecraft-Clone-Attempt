#pragma once
#include "raylib.h"
#include <map>
#include "raymath.h"
#include <vector>
#include <string>
#include "rlgl.h"

static std::vector<Texture> block_textures;

static Material block_material;

struct intVec3
{
	int x, y, z;
};

struct TextureFaces {
	Texture top;
	Texture bottom;
	Texture front;
	Texture back;
	Texture right;
	Texture left;

	void AllFaces(Texture texture) { top = bottom = front = back = right = left = texture; }

	void AllSides(Texture texture) { front = back = right = left = texture; }
};

class Block
{
	intVec3 pos;
	char id;
public:
	static void LoadTextures();
	Block();
	Block(intVec3 pos,unsigned char id) : pos(pos),id(id) {}
	TextureFaces GetTexture();
	friend class Chunk;
};

class Chunk
{
	static constexpr int CHUNK_WIDTH = 16;
	static constexpr int CHUNK_HEIGHT = 50;
	Chunk* right_chunk = nullptr;
	Chunk* left_chunk = nullptr;
	Chunk* front_chunk = nullptr;
	Chunk* back_chunk = nullptr;
	Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
	Vector3 pos;
	Model* plane = nullptr;;
public:
	Chunk(Vector3 pos, Image* noise, Model* block_face);
	void Generate(Image* noise);
	void AddRightChunk(Chunk* right) { right_chunk = right; }
	void AddLeftChunk(Chunk* left) { left_chunk = left; }
	void AddFrontChunk(Chunk* front) { front_chunk = front; }
	void AddBackChunk(Chunk* back) { back_chunk = back; }
	void Draw(Vector3 &player_pos);
	void DrawV2();
};
