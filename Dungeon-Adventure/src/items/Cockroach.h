#pragma once
#include "Entity.h"
#include "../tilemap/Tilemap.h"

#include "../gui/Label.h"

class Cockroach : public Entity {
private:
	Tilemap* _tileMap;

	int _dx, _dy;
	int _speed;
	int _directionCounter;

	SDL_Texture* _attackedTexture;
	int _attackedTextureTimer;

	int _health;

	gui::Font* _smallFont;
public:
	bool isAttacked;

public:
	Cockroach(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* map, const char* name);
	~Cockroach();

	void tick() override;
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) override;
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, std::vector<LightEmitter*>& lightEmitters) override;

	inline int getHealth() const { return _health; }
};
