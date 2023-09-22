#include "Player.h"

Player::Player(Vector3 pos, Vector3 size) : Entity(pos,size)
{
	camera.position = pos;
	camera.projection = CAMERA_CUSTOM;
	camera.up = { 0,1.0f,0 };
	camera.fovy = 60;
	camera.target = { 1.0f, 0, 1.0f };
	mode = MovementMode::walk;
	state = PlayerState::air;
}

void Player::BindCam(Vector3 offset)
{
	camera.position = Vector3Add(pos, offset);
}

void Player::Update()
{
	BindCam(Vector3{ 0,0.5,0 });
	UpdateState();
	Rotate();
	Move();
}

void Player::Rotate()
{
	if (IsKeyDown(KEY_LEFT))
	{
		orientation.x -= GetFrameTime();
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		orientation.x += GetFrameTime();
	}

	if (IsKeyDown(KEY_UP))
	{
		orientation.y += GetFrameTime()/4.f;
	}

	if (IsKeyDown(KEY_DOWN))
	{
		orientation.y -= GetFrameTime()/4.f;
	}

	orientation.x += GetMouseDelta().x * GetFrameTime() * MouseSensitivity;
	orientation.y -= GetMouseDelta().y * GetFrameTime() * MouseSensitivity;

	SetMousePosition(GetScreenWidth() / 2.f, GetScreenHeight() / 2.f);

	if (orientation.x > 2 * PI) orientation.x = 0;
	if (orientation.x < 0) orientation.x = 2 * PI;
	if (orientation.y > PI/2) orientation.y = PI/2;
	if (orientation.y < -PI/2) orientation.y = -PI/2;

	camera.target = Vector3Add(camera.position, { cosf(orientation.x) , sinf(orientation.y), sinf(orientation.x) });
}

void Player::UpdateState()
{
	if (pos.y <= 0)
	{
		state = PlayerState::grounded;
	}
}

void Player::Move()
{
	Vector3 look_dir = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
	Vector3 side_dir = { cosf(orientation.x + PI / 2), 0, sinf(orientation.x + PI / 2) };

	if (mode != MovementMode::fly)
	{
		//look_dir.y = 0;
	}

	if (IsKeyDown(KEY_SPACE))
	{
		pos = Vector3Add(pos, Vector3Scale({ 0,1,0 }, speed * GetFrameTime()));
	}

	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		pos = Vector3Add(pos, Vector3Scale({ 0,-1,0 }, speed * GetFrameTime()));
	}

	if (IsKeyDown(KEY_W))
	{
		pos = Vector3Add(pos, Vector3Scale(look_dir, speed*GetFrameTime()));
	}

	if (IsKeyDown(KEY_S))
	{
		pos = Vector3Subtract(pos, Vector3Scale(look_dir, speed*GetFrameTime()));
	}

	if (IsKeyDown(KEY_D))
	{
		pos = Vector3Add(pos, Vector3Scale(side_dir, speed*GetFrameTime()));
	}

	if (IsKeyDown(KEY_A))
	{
		pos = Vector3Subtract(pos, Vector3Scale(side_dir, speed*GetFrameTime()));
	}

}

void Player::Draw()
{
	DrawBoundingBox(hitbox, WHITE);
}
