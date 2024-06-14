#pragma once
#include <iostream>
#include <vector>

#include "Entity.h"
#include "InventoryItem.h"

#include "../gui/Label.h"

class Tilemap;

class Player: public Entity {
private:
	Tilemap* _tileMap;

	int _dx, _dy;
	int _speed;

	bool _isAttacking;
	SDL_Rect* _leftSwordAnimationRects, * _rightSwordAnimationRects, * _upSwordAnimationRects, * _downSwordAnimationRects;
	SDL_Rect _attackHitBoxRect;
	int _hitDistance;

	// Player health
	SDL_Texture* _healthTextures[7];
	SDL_Texture* _currentHealthImage;
	int _health;
	int _spikeHealthDecrementCounter;
	bool _isHealthLow;
	int _alpha, _alphaIncrement;

	// Inventory
	std::vector<InventoryItem*> _inventoryItems;
	gui::Font* _fontSmall, *_fontLarge;

public:
	bool _hasMap;

public:
	Player(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* tileMap, const char* name);
	~Player();

	void tick() override;
	void tick(std::vector<GameObject*>& gameObjects, std::vector<Entity*>& entities);
	void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) override;

	bool checkAttackCollision(Entity* another); // For player attack collision

	void playAttackAnimation();
	SDL_Texture* loadExtraTextures(const char* filePath);
};

