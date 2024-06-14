#include <iostream>

#include "GameObject.h"
#include "../utils/Macros.h"

SDL_Renderer* GameObject::_renderer;
GameObject::GameObject(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName): _x(x), _y(y), _width(width),
_height(height), _objectImage(nullptr), _animationClipRects(nullptr), objectName(objectName) {

	_renderer = renderer;
	_currentClipRect = { 0, 0, 0, 0 };

	_objectImage = IMG_LoadTexture(_renderer, path);
	if (_objectImage == nullptr) {
		ASSERT_LOG("Failed to load game object's texture.");
	}

	// Retrieve the width and height of the texture image
	SDL_QueryTexture(_objectImage, NULL, NULL, &_currentClipRect.w, &_currentClipRect.h);

	_animationCounter = 0;
	_animationSpeed = 3; // Default animation speed for all game objects. Can change using the animation speed setter function.
	_maxFrames = 0;
	_currentFrame = 0;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(_objectImage);
}

void GameObject::playAnimation() {
	ASSERT_CONDITIONAL(_animationClipRects == nullptr, "Animations clip rects have not been set up.");
	
	_animationCounter += _animationSpeed;
	if (_animationCounter > 60) {
		_animationCounter = 0;
		_currentFrame++;
		if (_currentFrame > _maxFrames - 1) {
			_currentFrame = 0;
		}
	}

	_currentClipRect = _animationClipRects[_currentFrame];
}
void GameObject::setAnimationClipRects(SDL_Rect* animationClipRects, int frames) {
	_animationClipRects = animationClipRects;
	_maxFrames = frames;
}

void GameObject::setAnimationSpeed(int animationSpeed) {
	_animationSpeed = animationSpeed;
}

int GameObject::getXPos() const {
	return _x;
}

int GameObject::getYPos() const {
	return _y;
}

int GameObject::getWidth() const {
	return _width;
}

int GameObject::getHeight() const {
	return _height;
}
