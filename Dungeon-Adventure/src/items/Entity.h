#pragma once
#include "GameObject.h"

class Tilemap;

struct CollisionAxes {
	bool xCollision = false, yCollision = false;
};

class Entity {
protected:
	static SDL_Renderer* _renderer;
	int _x, _y, _width, _height;
	SDL_Texture* _entityImage;

	char _directions[5];
	char _currentDirection;

	SDL_Rect* _leftAnimationRects, *_rightAnimationRects, *_upAnimationRects, *_downAnimationRects;
	SDL_Rect _currentClipRect;
	SDL_Rect _collideRect;

	int _animationCounter, _animationSpeed, _maxFrames, _currentFrame;

public:
	Entity(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer);
	~Entity();

	virtual void tick() = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) = 0;

	void setDirectionAnimationClipRects(SDL_Rect* left, SDL_Rect* right, SDL_Rect* up, SDL_Rect* down, int frames);
	void playDirectionAnimation();

	CollisionAxes checkCollision(const Entity& another, int& dx, int& dy);
	CollisionAxes checkCollision(Tilemap* tileMap, int& dx, int& dy);

	inline int getXPos() const { return _x; }
	inline int getYPos() const { return _y; }
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
};

