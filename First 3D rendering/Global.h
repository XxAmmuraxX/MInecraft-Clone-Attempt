#pragma once

#define GROUND_LEVEL = 0;
#define JUMP_HEIGHT = 2;
constexpr float BLOCK_SIZE = 0.25;

constexpr float MouseSensitivity = 0.1f;

enum class PlayerState {
	grounded, air
};

enum class MovementMode {
	walk, fly
};