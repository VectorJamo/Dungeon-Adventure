#include "Spike.h"

#include "../launcher/Display.h"
#include "../effects/Light.h"

Spike::Spike(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName): GameObject(x, y, width, height, path, renderer, objectName) {
	_animationClipRects = new SDL_Rect[5];
	_animationClipRects[0] = { 0, 0, 25, 21 };
	_animationClipRects[1] = { 25, 0, 25, 21 };
	_animationClipRects[2] = { 25*2, 0, 25, 21 };
	_animationClipRects[3] = { 25*3, 0, 25, 21 };
	_animationClipRects[4] = { 25*4, 0, 25, 21 };

	_currentClipRect = _animationClipRects[4];

	setAnimationClipRects(_animationClipRects, 5);
	_animationSpeed = 5;
}

Spike::~Spike() {
	delete[] _animationClipRects;
}

void Spike::tick() {
	playAnimation();
}

void Spike::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters) {
	int spikeWorldX = _x;
	int spikeWorldY = _y;
	int spikeScreenX = spikeWorldX - ((playerX + playerWidth / 2) - Display::getWidth() / 2);
	int spikeScreenY = spikeWorldY - ((playerY + playerHeight / 2) - Display::getHeight() / 2);

	// Calculate lighting
	// Light from the player
	float intensity = 20000 / pow(sqrt(pow((playerX - spikeWorldX), 2) + pow((playerY - spikeWorldY), 2)), 2);
	// Light from light emitting sources
	for (auto& emitter : lightEmitters) {
		intensity += emitter->intensityMultiplier / pow(sqrt(pow((emitter->lightPosX - spikeWorldX), 2) + pow((emitter->lightPosY - spikeWorldY), 2)), 2);
	}
	float alpha = intensity * 255;

	if (alpha < 50) {
		alpha = 50;
	}
	else if (alpha > 255) {
		alpha = 255;
	}
	SDL_SetTextureAlphaMod(_objectImage, alpha);

	if (spikeScreenX + _width >= 0 && spikeScreenX + _width <= Display::getWidth() + _width &&
		spikeScreenY + _height >= 0 && spikeScreenY + _height <= Display::getHeight() + _height) {

		SDL_Rect dest = { spikeScreenX, spikeScreenY, _width, _height };

		SDL_RenderCopy(_renderer, _objectImage, &_currentClipRect, &dest);
	}

}
