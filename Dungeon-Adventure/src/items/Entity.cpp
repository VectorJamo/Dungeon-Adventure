#include <iostream>

#include "Entity.h"
#include "../utils/Macros.h"

#include "../tilemap/Tilemap.h"

SDL_Renderer* Entity::_renderer;
Entity::Entity(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* name): _x(x), _y(y), _width(width),
_height(height), _entityImage(nullptr), name(name) {

	_renderer = renderer;
	_currentClipRect = { 0, 0, 0, 0 };
	_collideRect = _currentClipRect;

	_directions[0] = 'L';
	_directions[1] = 'R';
	_directions[2] = 'U';
	_directions[3] = 'D';

	_currentDirection = 'D';

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
	_animationSpeed = 10; // Default animation speed for all game objects. Can change using the animation speed setter function.
	_maxFrames = 0;
	_currentFrame = 0;

	_textureModTimer = 0;
	_alphaModTimer = 0;
	_maxModTime = 0;
}

Entity::~Entity() {
	SDL_DestroyTexture(_entityImage);
}

void Entity::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, std::vector<LightEmitter*>& lightEmitters) {
	// PASS
}

void Entity::updateTextureMods() {
	if (_maxModTime != 0) {
		std::cout << "Applying mod" << std::endl;
		_textureModTimer++;
		SDL_SetTextureColorMod(_entityImage, _currentModR, _currentModG, _currentModB);

		if (_textureModTimer > _maxModTime) {
			_textureModTimer = 0;
			_maxModTime = 0;
			std::cout << "STOPPED!" << std::endl;
		}
	}
}

void Entity::setTextureModulation(char r, char g, char b, int time) {
	_currentModR = r;
	_currentModG = g;
	_currentModB = b;
	_maxModTime = time;

	// TODO
	SDL_SetTextureColorMod(_entityImage, r, g, b);
}

void Entity::setTextureAlphaModulation(char a, int time) {
	// TODO
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

CollisionAxes Entity::checkCollision(Tilemap* tileMap, int& dx, int& dy) {
	CollisionAxes type;

	for (int i = 0; i < tileMap->getMapRows(); i++) {
		for (int j = 0; j < tileMap->getMapCols(); j++) {

			unsigned char** tiles = tileMap->getTileMap();

			if (tiles[i][j] == '1') {
				int tileX = j * tileMap->getTileSize();
				int tileY = i * tileMap->getTileSize();

				// First set the player's X to the new X and check if collision occurs,
				float entityXNew = (getXPos() + _collideRect.x) + dx;
				if (!(entityXNew > tileX + tileMap->getTileSize() || entityXNew + (_collideRect.w) < tileX || (getYPos() + _collideRect.y) + _collideRect.h < tileY ||
					getYPos() + _collideRect.y > tileY + tileMap->getTileSize())) {
					type.xCollision = true;
				}
				// Then, set the player's Y to the new Y and check if collision occurs
				float entityYNew = (getYPos() + _collideRect.y) + dy;
				if (!(getXPos() + _collideRect.x > tileX + tileMap->getTileSize() || (getXPos() + _collideRect.x) + _collideRect.w < tileX ||
					(entityYNew + _collideRect.h) < tileY || entityYNew > tileY + tileMap->getTileSize())) {
					type.yCollision = true;
				}
			}
		}
	}
	return type;
}


CollisionAxes Entity::checkCollision(GameObject* object, int& dx, int& dy) {
	CollisionAxes axes;

	int entityWorldX = _x;
	int entityWorldY = _y;
	int objectWorldX = object->getXPos();
	int objectWorldY = object->getYPos();

	float entityWorldXNew = entityWorldX + dx;
	if (!(entityWorldXNew + _collideRect.x +  _collideRect.w < objectWorldX || entityWorldXNew + _collideRect.x > objectWorldX + object->getWidth() ||
		(entityWorldY + _collideRect.y) + _collideRect.h < object->getYPos() || entityWorldY + _collideRect.y > object->getYPos() + object->getHeight())) {
		axes.xCollision = true;
	}
	float entityWorldYNew = entityWorldY + dy;
	if (!(entityWorldX + _collideRect.x + _collideRect.w < objectWorldX || entityWorldX + _collideRect.x > objectWorldX + object->getWidth() ||
		(entityWorldYNew + _collideRect.y) + _collideRect.h < object->getYPos() || entityWorldYNew + _collideRect.y > object->getYPos() + object->getHeight())) {
		axes.yCollision = true;
	}

	return axes;
}

int Entity::getXPos() const {
	return _x;
}
int Entity::getYPos() const {
	return _y;
}
int Entity::getWidth() const {
	return _width;
}
int Entity::getHeight() const {
	return _height;
}