#include "Cockroach.h"

#include "../launcher/Display.h"
#include "../effects/Light.h"

#include <cstdlib>
#include <iostream>

#include "../effects/Light.h"

#include "../gui/GUI_Manager.h"

#include "../states/GameState.h"

Cockroach::Cockroach(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* map, const char* name) : Entity(x, y, width, height, path, renderer, name) {	
	_tileMap = map;

	_dx = 0;
	_dy = 0;
	_speed = 1;
	_directionCounter = 0;


	_currentClipRect = { 0, 0, 32, 32 };
	_collideRect = { 0, 0, width, height };
	_currentDirection = _directions[rand() % 4];
	std::cout << rand()%4 << std::endl;

	_leftAnimationRects = new SDL_Rect[3];
	_rightAnimationRects = new SDL_Rect[3];
	_upAnimationRects = new SDL_Rect[3];
	_downAnimationRects = new SDL_Rect[3];

	_leftAnimationRects[0] = { 0, 32 * 3, 32, 32 };
	_leftAnimationRects[1] = { 32, 32 * 3, 32, 32 };
	_leftAnimationRects[2] = { 32*2, 32 * 3, 32, 32 };

	_rightAnimationRects[0] = { 0, 0, 32, 32 };
	_rightAnimationRects[1] = { 32, 0, 32, 32 };
	_rightAnimationRects[2] = { 32 * 2, 0, 32, 32 };

	_upAnimationRects[0] = { 0, 32, 32, 32 };
	_upAnimationRects[1] = { 32, 32, 32, 32 };
	_upAnimationRects[2] = { 32 * 2, 32, 32, 32 };

	_downAnimationRects[0] = { 0, 32 * 2, 32, 32 };
	_downAnimationRects[1] = { 32, 32 * 2, 32, 32 };
	_downAnimationRects[2] = { 32 * 2, 32 * 2, 32, 32 };

	setDirectionAnimationClipRects(_leftAnimationRects, _rightAnimationRects, _upAnimationRects, _downAnimationRects, 3);

	_attackedTexture = IMG_LoadTexture(_renderer, "res/images/roach-attacked.png");
	
	isAttacked = false;
	_attackedTextureTimer = 0;

	_health = 100;

	_smallFont = new gui::Font("res/fonts/roboto/Roboto-Regular.ttf", 16);
}

Cockroach::~Cockroach() {
	delete _smallFont;

	delete[] _leftAnimationRects;
	delete[] _rightAnimationRects;
	delete[] _upAnimationRects;
	delete[] _downAnimationRects;
}

void Cockroach::tick() {

	if (isAttacked) {
		isAttacked = false;

		_attackedTextureTimer = 1;
		_health--;

		if (_health % 10 == 0) {
			gui::GUI_Manager::AddTempText(Display::getWidth()/2 - 30, Display::getHeight()/2 - 30, "+1", _smallFont, 120, _renderer);
			GameState::setPoints(GameState::getPoints() + 1);
		}
	}

	if (_attackedTextureTimer != 0) {
		_attackedTextureTimer++;
		if (_attackedTextureTimer > 5) { 
			_attackedTextureTimer = 0;
		}
	}
	else {
		updateTextureMods();
		playDirectionAnimation();
		if (_currentDirection == 'D') {
			_dy = _speed;
		}
		else if (_currentDirection == 'U') {
			_dy = -_speed;
		}
		else if (_currentDirection == 'L') {
			_dx = -_speed;
		}
		else if (_currentDirection == 'R') {
			_dx = _speed;
		}

		CollisionAxes axes = this->checkCollision(_tileMap, _dx, _dy);
		if (axes.xCollision) {
			_dx = 0;

			int index = rand() % 4;
			_currentDirection = _directions[index];
		}
		if (axes.yCollision) {
			_dy = 0;

			int index = rand() % 4;
			_currentDirection = _directions[index];
		}

		_directionCounter++;
		if (_directionCounter > 120) { // Approx. 2 seconds
			_directionCounter = 0;

			int index = rand() % 4;
			_currentDirection = _directions[index];
		}

		_x += _dx;
		_y += _dy;
	}
}

void Cockroach::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) {

	int roachWorldX = _x;
	int roachWorldY = _y;
	int roachScreenX = roachWorldX - ((playerX + playerWidth / 2) - Display::getWidth() / 2);
	int roachScreenY = roachWorldY - ((playerY + playerHeight / 2) - Display::getHeight() / 2);
	if (_attackedTextureTimer == 0) {
		SDL_Rect dest = { roachScreenX, roachScreenY, _width, _height };

		SDL_RenderCopy(_renderer, _entityImage, &_currentClipRect, &dest);
	}
	else {
		SDL_Rect dest = { roachScreenX, roachScreenY, _width, _height };

		SDL_RenderCopy(_renderer, _attackedTexture, NULL, &dest);
	}
	_dx = 0;
	_dy = 0;
}

void Cockroach::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, std::vector<LightEmitter*>& lightEmitters) {
	int roachWorldX = _x;
	int roachWorldY = _y;
	int roachScreenX = roachWorldX - ((playerX + playerWidth / 2) - Display::getWidth() / 2);
	int roachScreenY = roachWorldY - ((playerY + playerHeight / 2) - Display::getHeight() / 2);

	// Calculate lighting
	// Light from the player
	float intensity = 20000 / pow(sqrt(pow((playerX - roachWorldX), 2) + pow((playerY - roachWorldY), 2)), 2);

	// Light from light emitting sources
	for (auto& emitter : lightEmitters) {
		intensity += emitter->intensityMultiplier / pow(sqrt(pow((emitter->lightPosX - roachWorldX), 2) + pow((emitter->lightPosY - roachWorldY), 2)), 2);
	}
	float alpha = intensity * 255;

	if (alpha < 50) {
		alpha = 50;
	}
	else if (alpha > 255) {
		alpha = 255;
	}

	if (_attackedTextureTimer == 0) {
		SDL_SetTextureAlphaMod(_entityImage, alpha);
		SDL_Rect dest = { roachScreenX, roachScreenY, _width, _height };

		SDL_RenderCopy(_renderer, _entityImage, &_currentClipRect, &dest);
	}
	else {
		SDL_Rect dest = { roachScreenX, roachScreenY, 12, 12 };

		SDL_RenderCopy(_renderer, _attackedTexture, NULL, &dest);
	}
	_dx = 0;
	_dy = 0;
}
