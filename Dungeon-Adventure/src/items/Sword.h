#pragma once
#include "GameObject.h"

class Sword: public GameObject {
private:

public:
	Sword(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName);
	~Sword();

	void tick() override;
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters) override;

};

