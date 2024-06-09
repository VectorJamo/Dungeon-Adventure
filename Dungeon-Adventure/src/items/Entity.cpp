#include <iostream>

#include "Entity.h"
#include "../utils/Macros.h"

SDL_Renderer* Entity::_renderer;
Entity::Entity(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer): _x(x), _y(y), _width(width),
_height(height), _entityImage(nullptr){

	_renderer = renderer;
	_currentClipRect = { 0, 0, 0, 0 };
	_directions[0] = 'L';
	_directions[1] = 'R';
	_directions[2] = 'U';
	_directions[3] = 'D';
	_directions[3] = 'X';

	_currentDirection = 'X';

	_leftAnimationRects = nullptr;
	_rightAnimationRects = nullptr;
	_upAnimationRects = nullptr;
	_downAnimationRects = nullptr;

	// Load the entity's image
	_entityImage = IMG_LoadTexture(_renderer, path);
	if (_entityImage == nullptr) {
		ASSERT_LOG("Failed to load entity's texture.");
	}

	// Retrieve the width and height of the texture image
	SDL_QueryTexture(_entityImage, NULL, NULL, &_currentClipRect.w, &_currentClipRect.h);

	_animationCounter = 0;
	_animationSpeed = 1; // Default animation speed for all game objects. Can change using the animation speed setter function.
	_maxFrames = 0;
	_currentFrame = 0;
}

Entity::~Entity() {
	SDL_DestroyTexture(_entityImage);
}

void Entity::setDirectionAnimationClipRects(SDL_Rect* left, SDL_Rect* right, SDL_Rect* up, SDL_Rect* down, int frames) {
	_leftAnimationRects = left;
	_rightAnimationRects = right;
	_upAnimationRects = up;
	_downAnimationRects = down;

	_maxFrames = frames;
}

void Entity::playDirectionAnimation() {
	ASSERT_CONDITIONAL(_leftAnimationRects == nullptr, "Animations clip rects have not been set up.");

	_animationCounter += _animationSpeed;
	if (_animationCounter > 60) {
		_animationCounter = 0;
		_currentFrame++;
		if (_currentFrame > _maxFrames - 1) {
			_currentFrame = 0;
		}
	}

	if (_currentDirection == 'L') {
		_currentClipRect = _leftAnimationRects[_currentFrame];
	}
	else if (_currentDirection == 'R') {
		_currentClipRect = _rightAnimationRects[_currentFrame];
	}
	else if (_currentDirection == 'U') {
		_currentClipRect = _upAnimationRects[_currentFrame];
	}
	else if(_currentDirection == 'D') {
		_currentClipRect = _downAnimationRects[_currentFrame];
	}
}
