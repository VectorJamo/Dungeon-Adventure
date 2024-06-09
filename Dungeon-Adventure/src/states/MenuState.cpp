#include <iostream>

#include "MenuState.h"
#include "../utils/Macros.h"

using namespace gui;

MenuState::MenuState(SDL_Renderer* renderer): StateManager(renderer), _font(nullptr), _gameText(nullptr) {
	_font = new Font("res/fonts/roboto/Roboto-Regular.ttf", 36);

	_gameText = new Label(0, 0, "Dungeon Shooter", _font, renderer);
}

MenuState::~MenuState() {
	delete _gameText;

	delete _font;
}

void MenuState::tick() {
	std::cout << "From menu state." << std::endl;
}

void MenuState::render() {
	_gameText->render();
}
