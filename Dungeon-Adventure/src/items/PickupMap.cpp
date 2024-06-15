#include "PickupMap.h"
#include "../launcher/Display.h"
#include "../items/Torch.h"
Map::Map(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName): GameObject(x, y, width, height, path, renderer, objectName) {

}

Map::~Map() {

}

void Map::tick() {

}

void Map::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters) {
	int mapWorldX = _x;
	int mapWorldY = _y;
	int mapScreenX = mapWorldX - ((playerX + playerWidth / 2) - Display::getWidth() / 2);
	int mapScreenY = mapWorldY - ((playerY + playerHeight / 2) - Display::getHeight() / 2);
	
	// Calculate lighting
	// Light from the player
	float intensity = 20000 / pow(sqrt(pow((playerX - mapWorldX), 2) + pow((playerY - mapWorldY), 2)), 2);

	// Light from light emitting sources
	for (auto& emitter : lightEmitters) {
		intensity += emitter->intensityMultiplier / pow(sqrt(pow((emitter->lightPosX - mapWorldX), 2) + pow((emitter->lightPosY - mapWorldY), 2)), 2);
	}
	float alpha = intensity * 255;

	if (alpha < 50) {
		alpha = 50;
	}
	else if (alpha > 255) {
		alpha = 255;
	}
	SDL_SetTextureAlphaMod(_objectImage, alpha);

	SDL_Rect dest = { mapScreenX, mapScreenY, _width, _height };
	SDL_RenderCopy(_renderer, _objectImage, NULL, &dest);
}