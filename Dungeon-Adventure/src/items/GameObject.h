#pragma once
#include <SDL.h>
#include <SDL_image.h>

class GameObject {
protected:
	static SDL_Renderer* _renderer;
	int _x, _y, _width, _height;
	
	SDL_Texture* _objectImage;
	SDL_Rect* _animationClipRects;
	SDL_Rect _currentClipRect;
	
	int _animationCounter, _animationSpeed, _maxFrames, _currentFrame;

public:
	GameObject(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer);
	~GameObject();

	virtual void tick() = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) = 0;

	void playAnimation();
	void setAnimationClipRects(SDL_Rect* animationClipRects, int frames);
	void setAnimationSpeed(int animationSpeed);
};

