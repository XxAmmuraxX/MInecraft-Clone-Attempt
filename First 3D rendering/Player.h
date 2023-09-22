#pragma once
#include "Entity.h"

class Player : public Entity
{
	Camera camera;
	PlayerState state;
	MovementMode mode;
	float speed = 10;

	public:
		Player(Vector3 pos, Vector3 size);
		Camera* GetCam() { return &camera; }
		void BindCam(Vector3 offset);
		void Update();
		void Rotate();
		void UpdateState();
		void Move();
		void Draw();
};