#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Tilemap {
private:
	SDL_Renderer* _renderer;
	static int _mapCols, _mapRows;
	static int _tileSize;

	unsigned char** _tileMap;

	SDL_Texture* _mapSprite;

private:
	void loadTileMap(const char* filePath);

public:
	Tilemap(const char* mapPath, const char* spritePath, int mapRows, int mapCols, int tileSize, SDL_Renderer* renderer);
	~Tilemap();

	void tick();
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight);

	inline unsigned char** getTileMap() { return _tileMap; }
	inline static int getTileSize() { return _tileSize; }
	inline static int getMapRows() { return _mapRows; }
	inline static int getMapCols() { return _mapCols; }
};

