#include <iostream>
#include "Player.h"

#include "../launcher/Display.h"
#include "../tilemap/Tilemap.h"

Player::Player(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* tileMap): Entity(x, y, width, height, path, renderer) {
	_tileMap = tileMap;
	_dx = 0;
	_dy = 0;
	_speed = 3;

	_currentClipRect = { 0, 0, 32, 32 };
	_collideRect = { 16, 16, 32, 32 };
}

Player::~Player() {
}

void Player::tick() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_A]) {
		_dx = -_speed;
	}
	if (keyState[SDL_SCANCODE_D]) {
		_dx = _speed;
	}
	if (keyState[SDL_SCANCODE_W]) {
		_dy = -_speed;
	}
	if (keyState[SDL_SCANCODE_S]) {
		_dy = _speed;
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
}
