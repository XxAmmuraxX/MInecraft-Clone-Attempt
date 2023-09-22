#include "Entity.h"

Entity::Entity(Vector3 pos, Vector3 size) :
	pos(pos), size(size), orientation(Vector2Zero())
{
	hitbox.min = Vector3{ pos.x - size.x / 2,pos.y - size.y / 2, pos.z - size.z / 2 };
	hitbox.max = Vector3{ pos.x + size.x / 2,pos.y + size.y / 2, pos.z + size.z / 2 };
}

void Entity::UpdateHitbox()
{
	hitbox.min = Vector3{ pos.x - size.x / 2,pos.y - size.y / 2, pos.z - size.z / 2 };
	hitbox.max = Vector3{ pos.x + size.x / 2,pos.y + size.y / 2, pos.z + size.z / 2 };
}
