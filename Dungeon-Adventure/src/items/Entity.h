#pragma once
#include "GameObject.h"

class Entity {
protected:
	static SDL_Renderer* _renderer;
	int _x, _y, _width, _height;
	SDL_Texture* _entityImage;

	char _directions[5];
	char _currentDirection;

	SDL_Rect* _leftAnimationRects, *_rightAnimationRects, *_upAnimationRects, *_downAnimationRects;
	SDL_Rect _currentClipRect;

	int _animationCounter, _animationSpeed, _maxFrames, _currentFrame;

public:
	Entity(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer);
	~Entity();

	virtual void tick() = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) = 0;

	void setDirectionAnimationClipRects(SDL_Rect* left, SDL_Rect* right, SDL_Rect* up, SDL_Rect* down, int frames);
	void playDirectionAnimation();
};

