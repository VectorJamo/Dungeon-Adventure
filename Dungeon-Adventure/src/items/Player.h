#pragma once
#include "Entity.h"

class Tilemap;

class Player: public Entity {
private:
	Tilemap* _tileMap;

	int _dx, _dy;
	int _speed;



public:
	Player(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* tileMap);
	~Player();

	void tick() override;
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) override;
};

