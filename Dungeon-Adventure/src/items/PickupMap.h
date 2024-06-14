#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"

#include "../effects/Light.h"

class Map: public GameObject {
private:

public:
	Map(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName);
	~Map();

	void tick();
	void draw(const std::vector<LightEmitter*>& lightEmitters, int playerX, int playerY, int playerWidth, int playerHeight);
};

