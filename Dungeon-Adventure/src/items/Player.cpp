#include <iostream>
#include "Player.h"

#include "../launcher/Display.h"
#include "../tilemap/Tilemap.h"

#include "../gui/GUI_Manager.h"
#include "../utils/Macros.h"

#include "Cockroach.h"

Player::Player(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, Tilemap* tileMap, const char* name): Entity(x, y, width, height, path, renderer, name) {
	_tileMap = tileMap;
	_dx = 0;
	_dy = 0;
	_speed = 4;

	_currentClipRect = { 0, 0, 32, 32 };
	_collideRect = { 16, 16, 32, 32 };

	_leftAnimationRects = new SDL_Rect[4];
	_rightAnimationRects = new SDL_Rect[4];
	_upAnimationRects = new SDL_Rect[4];
	_downAnimationRects = new SDL_Rect[4];
	_leftSwordAnimationRects = new SDL_Rect[4];
	_rightSwordAnimationRects = new SDL_Rect[4];
	_upSwordAnimationRects = new SDL_Rect[4];
	_downSwordAnimationRects = new SDL_Rect[4];

	_downAnimationRects[0] = { 0, 0, 32, 32 };
	_downAnimationRects[1] = { 32, 0, 32, 32 };
	_downAnimationRects[2] = { 32 * 2, 0, 32, 32 };
	_downAnimationRects[3] = { 32 * 3, 0, 32, 32 };

	_rightAnimationRects[0] = { 0, 32 * 2, 32, 32 };
	_rightAnimationRects[1] = { 32, 32 * 2, 32, 32 };
	_rightAnimationRects[2] = { 32 * 2, 32 * 2, 32, 32 };
	_rightAnimationRects[3] = { 32 * 3, 32 * 2, 32, 32 };

	_upAnimationRects[0] = { 0, 32 * 4, 32, 32 };
	_upAnimationRects[1] = { 32, 32 * 4, 32, 32 };
	_upAnimationRects[2] = { 32 * 2, 32 * 4, 32, 32 };
	_upAnimationRects[3] = { 32 * 3, 32 * 4, 32, 32 };

	_leftAnimationRects[0] = { 0, 32 * 6, 32, 32 };
	_leftAnimationRects[1] = { 32, 32 * 6, 32, 32 };
	_leftAnimationRects[2] = { 32 * 2, 32 * 6, 32, 32 };
	_leftAnimationRects[3] = { 32 * 3, 32 * 6, 32, 32 };

	// Sword animations
	_downSwordAnimationRects[0] = { 32 * 4, 0, 32, 32 };
	_downSwordAnimationRects[1] = { 32 * 5, 0, 32, 32 };
	_downSwordAnimationRects[2] = { 32 * 6, 0, 32, 32 };
	_downSwordAnimationRects[3] = { 32 * 7, 0, 32, 32 };

	_rightSwordAnimationRects[0] = { 32 * 4, 32 * 2, 32, 32 };
	_rightSwordAnimationRects[1] = { 32 * 5, 32 * 2, 32, 32 };
	_rightSwordAnimationRects[2] = { 32 * 6, 32 * 2, 32, 32 };
	_rightSwordAnimationRects[3] = { 32 * 7, 32 * 2, 32, 32 };

	_upSwordAnimationRects[0] = { 32 * 4, 32 * 4, 32, 32 };
	_upSwordAnimationRects[1] = { 32 * 5, 32 * 4, 32, 32 };
	_upSwordAnimationRects[2] = { 32 * 6, 32 * 4, 32, 32 };
	_upSwordAnimationRects[3] = { 32 * 7, 32 * 4, 32, 32 };

	_leftSwordAnimationRects[0] = { 32 * 4, 32 * 6, 32, 32 };
	_leftSwordAnimationRects[1] = { 32 * 5, 32 * 6, 32, 32 };
	_leftSwordAnimationRects[2] = { 32 * 6, 32 * 6, 32, 32 };
	_leftSwordAnimationRects[3] = { 32 * 7, 32 * 6, 32, 32 };

	_maxFrames = 4;

	_inventoryItems.reserve(5);

	// state variables
	_hasMap = false;
	_hasSword = false;

	_fontLarge = new gui::Font("res/fonts/roboto/Roboto-Thin.ttf", 48);
	_fontSmall = new gui::Font("res/fonts/roboto/Roboto-Thin.ttf", 28);

	_isAttacking = false;
	_hitDistance = 5;

	// Load health textures
	_healthTextures[0] = loadExtraTextures("res/images/health/0.png");
	_healthTextures[1] = loadExtraTextures("res/images/health/1.png");
	_healthTextures[2] = loadExtraTextures("res/images/health/2.png");
	_healthTextures[3] = loadExtraTextures("res/images/health/3.png");
	_healthTextures[4] = loadExtraTextures("res/images/health/4.png");
	_healthTextures[5] = loadExtraTextures("res/images/health/5.png");
	_healthTextures[6] = loadExtraTextures("res/images/health/6.png");

	_health = 100;
	
	_currentHealthImage = _healthTextures[(int)(_health/16)];
	_spikeHealthDecrementCounter = 0;
	_isHealthLow = false;

	_alpha = 255;
	_alphaIncrement = 15;
}

Player::~Player() {
	delete _fontSmall;
}

void Player::tick() {
	// PASS
}

void Player::tick(std::vector<GameObject*>& gameObjects, std::vector<Entity*>& entities) {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_SPACE]) {
		_isAttacking = true;

		playAttackAnimation();
	}
	else if (keyState[SDL_SCANCODE_A]) {
		_dx = -_speed;
		_currentDirection = 'L';

		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_D]) {
		_dx = _speed;
		_currentDirection = 'R';

		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_W]) {
		_dy = -_speed;
		_currentDirection = 'U';

		playDirectionAnimation();
	}
	else if (keyState[SDL_SCANCODE_S]) {
		_dy = _speed;
		_currentDirection = 'D';

		playDirectionAnimation();
	}
	// Player and tile collision
	CollisionAxes axes = checkCollision(_tileMap, _dx, _dy);
	if (axes.xCollision) {
		_dx = 0;
	}
	if (axes.yCollision) {
		_dy = 0;
	}

	// Player and game object collision
	for (GameObject* gameObject : gameObjects) {
		CollisionAxes axes = checkCollision(gameObject, _dx, _dy);
		if (axes.xCollision || axes.yCollision) {
			if (gameObject->objectName == "map" && !_hasMap) {
				// Display text
				gui::GUI_Manager::AddTempText(100, 100, "Picked up a map", _fontLarge, 240, _renderer);
				gui::GUI_Manager::AddTempText(100, 200, "Press 'M' to use.", _fontSmall, 240, _renderer);

				_hasMap = true;

				InventoryItem* item = new InventoryItem();
				item->name = "map";
				item->count = 1;

				_inventoryItems.push_back(item);
			}
			if (gameObject->objectName == "spike") {
				_spikeHealthDecrementCounter++;
				if (_spikeHealthDecrementCounter > 120) {
					_health -= 16;
					if (_health < 16) {
						std::cout << "Game Over." << std::endl;
						__debugbreak(); // TODO: IMPORTANT: REPLACE IT.
					}
					else if (_health < 32) {
						_isHealthLow = true;
					}
					_currentHealthImage = _healthTextures[(int)(_health / 16)];

					_spikeHealthDecrementCounter = 0;
				}
			}
		}
	}

	// Player and entity collision
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->name == "roach") {
			if (_isAttacking) {
				if (checkAttackCollision(entities[i])) {
					Cockroach* roach = ((Cockroach*)(entities[i]));

					if (roach->getHealth() > 0) {
						roach->isAttacked = true;
					}
					else {
						delete roach;

						entities.erase(entities.begin() + i);
						i--;
					}
				}
			}
		}
	}
	_x += _dx;
	_y += _dy;
}

void Player::render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) {

	SDL_Rect dest = { Display::getWidth()/2 - _width/2, Display::getHeight()/2 - _height/2, _width, _height};
	SDL_RenderCopy(_renderer, _entityImage, &_currentClipRect, &dest);

#if 0
	if (_isAttacking) {
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

		int attackHitBoxRectWorldX = _x + _attackHitBoxRect.x;
		int attackHitBoxRectWorldY = _y + _attackHitBoxRect.y;
		int attackHitBoxRectScreenX = attackHitBoxRectWorldX - ((_x + _width/ 2) - Display::getWidth() / 2);
		int attackHitBoxRectScreenY = attackHitBoxRectWorldY - ((_y + _height / 2) - Display::getHeight() / 2);

		SDL_Rect destRect = { attackHitBoxRectScreenX, attackHitBoxRectScreenY, _attackHitBoxRect.w, _attackHitBoxRect.h };
		SDL_RenderDrawRect(_renderer, &destRect);
	}
#endif
	SDL_Rect healthDest = { 10, 10, 100, 30 };
	if (_isHealthLow) {
		// TODO: FLASH THE HEALTH BAR
		_alpha += _alphaIncrement;
		if (_alpha >= 255) {
			_alphaIncrement = -15;
		}
		else if (_alpha <= 0) {
			_alphaIncrement = 15;
		}

		SDL_SetTextureAlphaMod(_currentHealthImage, _alpha);
		SDL_RenderCopy(_renderer, _currentHealthImage, NULL, &healthDest);
	}
	else {
		SDL_RenderCopy(_renderer, _currentHealthImage, NULL, &healthDest);
	}

	// Reset
	_dx = 0;
	_dy = 0;
	if (_currentDirection == 'L') {
		_currentClipRect = _leftAnimationRects[0];
	}
	else if (_currentDirection == 'R') {
		_currentClipRect = _rightAnimationRects[0];

	}
	else if (_currentDirection == 'U') {
		_currentClipRect = _upAnimationRects[0];

	}
	else if (_currentDirection == 'D') {
		_currentClipRect = _downAnimationRects[0];

	}

	_isAttacking = false;
}

bool Player::checkAttackCollision(Entity* another) {
	int attackRectWorldX = _x + _attackHitBoxRect.x;
	int attackRectWorldY = _y + _attackHitBoxRect.y;
	int attackRectWidth = _attackHitBoxRect.w;
	int attackRectHeight = _attackHitBoxRect.h;

	if (another->getXPos() > attackRectWorldX + attackRectWidth || another->getXPos() + another->getWidth() < attackRectWorldX ||
		another->getYPos() > attackRectWorldY + attackRectHeight || another->getYPos() + another->getHeight() < attackRectWorldY) {
		return false;
	}
	return true;
}

void Player::playAttackAnimation() {
	_animationCounter += _animationSpeed;
	if (_animationCounter > 60) {
		_animationCounter = 0;
		_currentFrame++;
		if (_currentFrame > _maxFrames - 1) {
			_currentFrame = 0;
		}
	}

	if (_currentDirection == 'L') {
		_currentClipRect = _leftSwordAnimationRects[_currentFrame];

		_attackHitBoxRect = { -_hitDistance + _collideRect.x, _collideRect.y, _hitDistance, _collideRect.h };
	}
	else if (_currentDirection == 'R') {
		_currentClipRect = _rightSwordAnimationRects[_currentFrame];

		_attackHitBoxRect = { _collideRect.x + _collideRect.w, _collideRect.y, _hitDistance, _collideRect.h };
	}
	else if (_currentDirection == 'U') {
		_currentClipRect = _upSwordAnimationRects[_currentFrame];

		_attackHitBoxRect = { _collideRect.x, _collideRect.y, _collideRect.w, -_hitDistance };
	}
	else if (_currentDirection == 'D') {
		_currentClipRect = _downSwordAnimationRects[_currentFrame];

		_attackHitBoxRect = { _collideRect.x, _collideRect.y + _collideRect.h, _collideRect.w, _hitDistance };
	}
}

SDL_Texture* Player::loadExtraTextures(const char* filePath) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(_renderer, filePath);

	ASSERT_CONDITIONAL(texture == nullptr, "Failed to load extra textures.");
	return texture;
}
