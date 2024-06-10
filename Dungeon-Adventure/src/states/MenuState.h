#pragma once
#include "StateManager.h"

#include "../launcher/Display.h"

#include "../gui/Label.h"
#include "../gui/Button.h"
#include "../gui/GUI_Manager.h"

class MenuState: public StateManager {
private:
	gui::Font* _fontExtraLarge;
	gui::Font* _fontLarge;
	gui::Font* _fontMedium;
	gui::Font* _fontSmall;

	gui::Font* _fontLargeLight;
	gui::Font* _fontMediumLight;
	gui::Font* _fontSmallLight;

	gui::Label* _gameText;
	gui::Label* _versionText;
	gui::Label* _copyrightText;

	gui::Button* _playButton;
	gui::Button* _quitButton;

public:
	MenuState(SDL_Renderer* renderer, bool *gameStatus);
	~MenuState();

	void tick() override;
	void render() override;
};

