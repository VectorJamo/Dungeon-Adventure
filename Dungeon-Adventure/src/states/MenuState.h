#pragma once
#include "StateManager.h"

#include "../launcher/Display.h"

#include "../gui/Label.h"
#include "../gui/Button.h"
#include "../gui/GUI_Manager.h"

class MenuState: public StateManager {
private:
	gui::Font* _font;

	gui::Label* _gameText;

public:
	MenuState(SDL_Renderer* renderer);
	~MenuState();

	void tick() override;
	void render() override;
};

