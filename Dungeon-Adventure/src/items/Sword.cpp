#include "Sword.h"

Sword::Sword(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* objectName): GameObject(x, y, width, height, path, _renderer, objectName) {
	
}

Sword::~Sword() {
}

void Sword::tick() {
}

void Sword::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, const std::vector<LightEmitter*>& lightEmitters) {
}
