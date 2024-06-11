#pragma once
#include  "GameObject.h"

#include "../effects/Light.h"

class Torch: public GameObject, public LightEmitter {
private:
	SDL_Rect* _clipRects;

public:
	Torch(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer);
	~Torch();

	void tick() override;
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) override;
};