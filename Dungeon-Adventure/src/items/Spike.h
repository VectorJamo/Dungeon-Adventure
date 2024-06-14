#pragma once
#include "GameObject.h"

class LightEmitter;

class Spike: public GameObject {
private:
	SDL_Rect* _animationClipRects;

public:
	Spike(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName);
	~Spike();

	void tick();
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters);

};

