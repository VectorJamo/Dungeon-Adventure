#include <iostream>
#include "Player.h"

#include "../launcher/Display.h"
#include "../tilemap/Tilemap.h"

Player::Player(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* tileMap): Entity(x, y, width, height, path, renderer) {
	_tileMap = tileMap;
	_dx = 0;
	_dy = 0;
	_speed = 4;

	_currentClipRect = { 0, 0, 32, 32 };
	_collideRect = { 16, 16, 32, 32 };

	_leftAnimationRects = new SDL_Rect[4];
	_rightAnimationRects = new SDL_Rect[4];
	_upAnimationRects = new SDL_Rect[4];
	_downAnimationRects = new SDL_Rect[4];

	_downAnimationRects[0] = { 0, 0, 32, 32 };
	_downAnimationRects[1] = { 32, 0, 32, 32 };
	_downAnimationRects[2] = { 32 * 2, 0, 32, 32 };
	_downAnimationRects[3] = { 32 * 3, 0, 32, 32 };

	_rightAnimationRects[0] = { 0, 32 * 2, 32, 32 };
	_rightAnimationRects[1] = { 32, 32 * 2, 32, 32 };
	_rightAnimationRects[2] = { 32 * 2, 32 * 2, 32, 32 };
	_rightAnimationRects[3] = { 32 * 3, 32 * 2, 32, 32 };

	_upAnimationRects[0] = { 0, 32 * 4, 32, 32 };
	_upAnimationRects[1] = { 32, 32 * 4, 32, 32 };
	_upAnimationRects[2] = { 32 * 2, 32 * 4, 32, 32 };
	_upAnimationRects[3] = { 32 * 3, 32 * 4, 32, 32 };

	_leftAnimationRects[0] = { 0, 32 * 6, 32, 32 };
	_leftAnimationRects[1] = { 32, 32 * 6, 32, 32 };
	_leftAnimationRects[2] = { 32 * 2, 32 * 6, 32, 32 };
	_leftAnimationRects[3] = { 32 * 3, 32 * 6, 32, 32 };

	_maxFrames = 4;
}

Player::~Player() {
}

void Player::tick() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_A]) {
		_dx = -_speed;
		_currentDirection = 'L';
		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_D]) {
		_dx = _speed;
		_currentDirection = 'R';
		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_W]) {
		_dy = -_speed;
		_currentDirection = 'U';
		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_S]) {
		_dy = _speed;
		_currentDirection = 'D';
		playDirectionAnimation();
	}
	// TODO: check collision
	CollisionAxes axes = checkCollision(_tileMap, _dx, _dy);
	if (axes.xCollision) {
		_dx = 0;
	}
	if (axes.yCollision) {
		_dy = 0;
	}
	_x += _dx;
	_y += _dy;
}

void Player::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) {

	SDL_Rect dest = { Display::getWidth()/2 - _width/2, Display::getHeight()/2 - _height/2, _width, _height};
	SDL_RenderCopy(_renderer, _entityImage, &_currentClipRect, &dest);

	// Reset
	_dx = 0;
	_dy = 0;
	_currentDirection = 'X';
	_currentClipRect = _downAnimationRects[0];
}
