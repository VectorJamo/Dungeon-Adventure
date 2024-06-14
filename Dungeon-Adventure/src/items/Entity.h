#pragma once
#include "GameObject.h"

class Tilemap;
class LightEmitter;

struct CollisionAxes {
	bool xCollision = false, yCollision = false;
};

class Entity {
protected:
	static SDL_Renderer* _renderer;
	int _x, _y, _width, _height;
	SDL_Texture* _entityImage;

	char _directions[4];
	char _currentDirection;

	SDL_Rect* _leftAnimationRects, *_rightAnimationRects, *_upAnimationRects, *_downAnimationRects;
	SDL_Rect _currentClipRect;
	SDL_Rect _collideRect;

	int _animationCounter, _animationSpeed, _maxFrames, _currentFrame;

	int _textureModTimer, _alphaModTimer;
	int _maxModTime;

	char _currentModR, _currentModG, _currentModB, _currentModA;
	
public:
	const char* name;

public:
	Entity(int x, int y, int width, int height, const char* path, SDL_Renderer* renderer, const char* name);
	~Entity();

	virtual void tick() = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight) = 0;
	virtual void render(const int& playerX, const int& playerY, const int& playerWidth, const int& playerHeight, std::vector<LightEmitter*>& lightEmitters);

	void updateTextureMods();
	void setTextureModulation(char r, char g, char b, int time);
	void setTextureAlphaModulation(char a, int time);

	void setDirectionAnimationClipRects(SDL_Rect* left, SDL_Rect* right, SDL_Rect* up, SDL_Rect* down, int frames);
	void playDirectionAnimation();

	CollisionAxes checkCollision(GameObject* object, int& dx, int& dy);
	CollisionAxes checkCollision(Tilemap* tileMap, int& dx, int& dy);

	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
};

