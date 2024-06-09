#pragma once
#include "Display.h"

#include "../states/StateManager.h"
#include "../states/MenuState.h"
#include "../states/GameState.h"

class Game {
private:
	Display* _display;

	StateManager* _activeState;
	
public:
	static bool running;

public:
	Game(int width, int height, const char* title);
	~Game();

	void run();
};

