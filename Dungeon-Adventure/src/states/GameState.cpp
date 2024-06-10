#include <iostream>

#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer,  bool* gameStatus): StateManager(renderer, gameStatus) {
	x = 0;
}

GameState::~GameState() {
}

void GameState::tick() {
	x += 1;
}

void GameState::render() {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	SDL_Rect rect = { x, 20, 50, 50 };
	SDL_RenderFillRect(_renderer, &rect);
}
