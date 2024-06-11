#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class LightEmitter;

class Tilemap {
private:
	SDL_Renderer* _renderer;
	static const int _mapCols = 100, _mapRows = 100;
	static const int _tileSize = 64;

	unsigned char** _tileMap;

	// Tile assets
	SDL_Texture* _wall, *_floor;

private:
	void loadTileMap(const char* filePath);

public:
	Tilemap(const char* mapPath, SDL_Renderer* renderer);
	~Tilemap();

	void tick();
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, const std::vector<LightEmitter*>& lightEmitters);

	inline unsigned char** getTileMap() { return _tileMap; }
	inline static int getTileSize() { return _tileSize; }
	inline static int getMapRows() { return _mapRows; }
	inline static int getMapCols() { return _mapCols; }
};

