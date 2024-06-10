#include <iostream>

#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer,  bool* gameStatus): StateManager(renderer, gameStatus) {
}

GameState::~GameState() {
}

void GameState::tick() {
}

void GameState::render() {
}
