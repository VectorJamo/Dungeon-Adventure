#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>

class LightEmitter;

class GameObject {
protected:
	static SDL_Renderer* _renderer;
	int _x, _y, _width, _height;
	
	SDL_Texture* _objectImage;
	SDL_Rect* _animationClipRects;
	SDL_Rect _currentClipRect;
	
	int _animationCounter, _animationSpeed, _maxFrames, _currentFrame;

public:
	const char* objectName;

public:
	GameObject(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName);
	~GameObject();

	virtual void tick() = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters) = 0;
	void playAnimation();
	void setAnimationClipRects(SDL_Rect* animationClipRects, int frames);
	void setAnimationSpeed(int animationSpeed);

	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
};

