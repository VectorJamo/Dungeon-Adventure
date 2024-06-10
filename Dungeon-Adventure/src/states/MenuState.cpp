#include <iostream>

#include "MenuState.h"
#include "../utils/Macros.h"
#include "../gui/GUI_Manager.h"

#include "GameState.h"

using namespace gui;

MenuState::MenuState(SDL_Renderer* renderer, bool* gameStatus): StateManager(renderer, gameStatus), _fontExtraLarge(nullptr), 
_fontLarge(nullptr), _fontMedium(nullptr), _fontSmall(nullptr), _fontLargeLight(nullptr), _fontMediumLight(nullptr), 
_fontSmallLight(nullptr), _gameText(nullptr), _versionText(nullptr), _copyrightText(nullptr), _playButton(nullptr), 
_quitButton(nullptr) {

	// Fonts
	_fontExtraLarge = new Font("res/fonts/roboto/Roboto-Regular.ttf", 56);
	_fontLarge = new Font("res/fonts/roboto/Roboto-Regular.ttf", 48);
	_fontMedium = new Font("res/fonts/roboto/Roboto-Regular.ttf", 32);
	_fontSmall = new Font("res/fonts/roboto/Roboto-Regular.ttf", 18);

	_fontLargeLight = new Font("res/fonts/roboto/Roboto-Light.ttf", 48);
	_fontMediumLight = new Font("res/fonts/roboto/Roboto-Light.ttf", 32);
	_fontSmallLight = new Font("res/fonts/roboto/Roboto-Light.ttf", 18);

	// Labels
	_gameText = new Label(0, 0, "Dungeon Shooter", _fontExtraLarge, renderer);
	_gameText->setPosition(Display::getWidth() / 2 - _gameText->getWidth() / 2, Display::getHeight() / 6);
	
	_versionText = new Label(0, 0, "v0.1", _fontSmallLight, _renderer);
	_versionText->setPosition(_gameText->getXPos() + _gameText->getWidth(), _gameText->getYPos());

	_copyrightText = new Label(0, 0, "Copyright (C) Suraj Neupane", _fontSmallLight, _renderer);
	_copyrightText->setPosition(Display::getWidth() - _copyrightText->getWidth() - 15, Display::getHeight() - _copyrightText->getHeight() - 10);

	// Buttons
	_playButton = new Button(0, 0, "Play", _fontMedium, _renderer);
	_playButton->setPaddingX(20);
	_playButton->setPosition(Display::getWidth() / 2 - _playButton->getWidth()/2, 
		Display::getHeight() / 2.15f);
	_playButton->setOutlineColor(100, 100, 100, 255);
	_playButton->setOutlineThickness(2);

	_quitButton = new Button(0, 0, "Quit", _fontMedium, _renderer);
	_quitButton->setPaddingX(20);
	_quitButton->setPosition(Display::getWidth() / 2 - _quitButton->getWidth() / 2,
		Display::getHeight() / 1.80f);
	_quitButton->setOutlineColor(100, 100, 100, 255);
	_quitButton->setOutlineThickness(2);

	GUI_Manager::AddButtonsToTrack(_playButton);
	GUI_Manager::AddButtonsToTrack(_quitButton);
}

MenuState::~MenuState() {
	delete _playButton;
	delete _quitButton;

	delete _versionText;
	delete _gameText;

	delete _fontExtraLarge;
	delete _fontLarge;
	delete _fontMedium;
	delete _fontSmall;

	delete _fontLargeLight;
	delete _fontMediumLight;
	delete _fontSmallLight;
}

void MenuState::tick() {
	// Buttons
	if (_playButton->isMouseOver) {
		_playButton->setTextColor(255, 255, 255, 255);
		_playButton->setColor(0, 0, 0, 255);
	}
	else {
		_playButton->setTextColor(0, 0, 0, 255);
		_playButton->setColor(255, 255, 255, 255);
	}
	if (_quitButton->isMouseOver) {
		_quitButton->setTextColor(255, 255, 255, 255);
		_quitButton->setColor(0, 0, 0, 255);
	}
	else {
		_quitButton->setTextColor(0, 0, 0, 255);
		_quitButton->setColor(255, 255, 255, 255);
	}

	if (_playButton->isClicked) {
		_playButton->isClicked = false;

		GUI_Manager::ClearAll();		
		StateManager::SetCurrentState(new GameState(_renderer, _gameStatus));
		return;
	}
	if (_quitButton->isClicked) {
		*_gameStatus = false;
		_playButton->isClicked = false;
	}
}

void MenuState::render() {
	_gameText->render();
	_versionText->render();
	_copyrightText->render();

	_playButton->render();
	_quitButton->render();
}
