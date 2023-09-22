#pragma once
#include "World.h"
#include "Global.h"

class Entity
{

protected:
	Vector3 pos;
	Vector2 orientation;
	Vector3 size;
	BoundingBox hitbox;

public:
	Entity(Vector3 pos,Vector3 size);
	virtual void Draw() = 0;
	void UpdateHitbox();
};