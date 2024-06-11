#include "Torch.h"
#include "../launcher/Display.h"

Torch::Torch(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer): 
	GameObject(x, y, width, height, path, renderer){

	_clipRects = new SDL_Rect[2];
	_clipRects[0] = { 0, 0, 32, 32 };
	_clipRects[1] = { 32, 0, 32, 32 };

	setAnimationClipRects(_clipRects, 2);

	lightPosX = _x;
	lightPosY = _y;
	intensityMultiplier = 10000;
}

Torch::~Torch() {
	delete _clipRects;
}

void Torch::tick() {
	playAnimation();

	lightPosX = _x;
	lightPosY = _y;
}

void Torch::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) {
	int torchWorldX = _x;
	int torchWorldY = _y;
	int torchScreenX = torchWorldX - ((playerX + playerWidth / 2) - Display::getWidth() / 2);
	int torchScreenY = torchWorldY - ((playerY + playerHeight / 2) - Display::getHeight() / 2);

	if (torchScreenX + _width >= 0 && torchScreenX + _width <= Display::getWidth() + _width &&
		torchScreenY + _height >= 0 && torchScreenY + _height <= Display::getHeight() + _height) {

		SDL_Rect dest = { torchScreenX, torchScreenY, _width, _height };

		SDL_RenderCopy(_renderer, _objectImage, &_currentClipRect, &dest);
	}
}